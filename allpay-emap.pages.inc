<?php

function allpay_shipping_map_page(){

  global $base_url;
  foreach ($_GET as $a => $b) {
		$data[$a]=$b;
	}
  try {
		$AL = new ECPayLogistics();
		$AL->Send = $data;
	} catch (Exception $e) {
		echo $e->getMessage();
	}
	$html = $AL->CvsMap('');
	echo $html;
}

function allpay_shipping_map_page_request(){

  global $base_url;

  if(empty($_POST)){
  		drupal_exit();
  }
  $MerchantID=$_POST['MerchantID'];
  $MerchantTradeNo=$_POST['MerchantTradeNo'];
  $LogisticsSubType=$_POST['LogisticsSubType'];
  $CVSStoreID=$_POST['CVSStoreID'];
  $CVSStoreName=$_POST['CVSStoreName'];
  $CVSAddress=$_POST['CVSAddress'];
  $CVSTelephone=$_POST['CVSTelephone'];
  $ExtraData=$_POST['ExtraData'];

  $profile_id=$ExtraData;

  $shipping_profile=commerce_customer_profile_load($profile_id);
  $shipping_profile->field_merchanttrade['und'][0]['value']=$MerchantTradeNo;
  $shipping_profile->field_logisticssubtype['und'][0]['value']=$LogisticsSubType;
  $shipping_profile->field_cvsstoreid['und'][0]['value']=$CVSStoreID;
  $shipping_profile->field_cvsstorename['und'][0]['value']=$CVSStoreName;
  $shipping_profile->field_cvsaddress['und'][0]['value']=$CVSAddress;
  $shipping_profile->field_csvtelephone['und'][0]['value']=$CVSTelephone;
  field_attach_update('commerce_customer_profile', $shipping_profile);
  $order_id=substr($MerchantTradeNo, 14);
  drupal_goto($base_url.'/checkout/'.$order_id.'/review');

}

function allpay_shipping_order_request(){
  global $base_url;

  try {

    //預設環境，若沒有設定則用測試環境。
    $status=variable_get('allpay_shipping_status','dev');
    if ($status == 'dev') {
      $MerchantID = ALLPAY_SHIPPING_TEST_MERCHANT_ID;
      $HashKey=ALLPAY_SHIPPING_TEST_HASHKEY;
      $HashIV=ALLPAY_SHIPPING_TEST_HASHIV;

    } else {
      $MerchantID = variable_get('allpay_shipping_MerchantID');
      $HashKey=variable_get('allpay_shipping_HashKey');
      $HashIV=variable_get('allpay_shipping_HashIV');
    }


    //檢查回傳結果
    $AL = new ECPayLogistics();
    $AL->HashKey = $HashKey;
    $AL->HashIV = $HashIV;
    $allpay_feedback = $AL->CheckOutFeedback();
    unset($AL);

    //將訂單狀態更新
    // Process allPay feedback
    if (count($allpay_feedback) < 1) {
        throw new Exception(ALLPAY_FEEDBACK_ERROR);
    } else {
        $MerchantID=$allpay_feedback['MerchantID'];
        $MerchantTradeNo=$allpay_feedback['MerchantTradeNo'];
        $RtnCode=$allpay_feedback['RtnCode'];
        $RtnMsg=$allpay_feedback['RtnMsg'];
        $AllPayLogisticsID=$allpay_feedback['AllPayLogisticsID'];
        $LogisticsType=$allpay_feedback['LogisticsType'];
        $LogisticsSubType=$allpay_feedback['LogisticsSubType'];
        $GoodsAmount=$allpay_feedback['GoodsAmount'];
        $UpdateStatusDate=$allpay_feedback['UpdateStatusDate'];
        $ReceiverName=$allpay_feedback['ReceiverName'];
        $ReceiverPhone=$allpay_feedback['ReceiverPhone'];
        $ReceiverCellPhone=$allpay_feedback['ReceiverCellPhone'];
        $ReceiverEmail=$allpay_feedback['ReceiverEmail'];
        $ReceiverAddress=$_POST['ReceiverAddress'];
        $CVSPaymentNo=$allpay_feedback['CVSPaymentNo'];
        $CVSValidationNo=$allpay_feedback['CVSValidationNo'];
        $BookingNote=$allpay_feedback['BookingNote'];

        $query = new EntityFieldQuery();
        $query->entityCondition('entity_type', 'commerce_customer_profile')
          ->entityCondition('bundle', 'recipient')
          ->propertyCondition('status', 1)
          ->fieldCondition('field_merchanttrade', 'value', $MerchantTradeNo, '=')
          ->fieldCondition('field_allpaylogisticsid', 'value', $AllPayLogisticsID, '=')
          // Run the query as user 1.
          ->addMetaData('account', user_load(1));

        $result = $query->execute();
        if (isset($result['commerce_customer_profile'])) {
          $profile_id = array_keys($result['commerce_customer_profile'])[0];
          $shipping_profile=commerce_customer_profile_load($profile_id);
          $RTNCODE=array(
            2030=>'sc',
            3024=>'sc',
            2063=>'achieve',
            2073=>'achieve',
            3018=>'achieve',
            2067=>'receive',
            3022=>'receive',
            2074=>'overdue',
            3020=>'overdue',
            300=>'pending',
            2001=>'handle'
          );
          $code=$Result['RtnCode'];
          $shipping_profile->field_rtncode['und'][0]['value']=$allpay_feedback['RtnCode'];
          $shipping_profile->field_rtnmsg['und'][0]['value']=$allpay_feedback['RtnMsg'];
          $shipping_profile->field_updatestatusdate['und'][0]['value']=$allpay_feedback['UpdateStatusDate'];
          $shipping_profile->field_cvspaymentno['und'][0]['value']=$allpay_feedback['CVSPaymentNo'];
          $shipping_profile->field_bookingnote['und'][0]['value']=$allpay_feedback['BookingNote'];
          $shipping_profile->field_shipping_status['und'][0]['value']=$RTNCODE[$code];
          field_attach_update('commerce_customer_profile', $shipping_profile);
          $result_msg='1|OK';
        }
    }

  } catch (Exception $e) {
      $error = $e->getMessage();
      // Set the failure result
      $result_msg = '0|'.$error;
  }
  echo $result_msg;
}

?>
