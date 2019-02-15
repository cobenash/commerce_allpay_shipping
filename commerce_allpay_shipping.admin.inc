<?php

/**
 * @file commerce_allpay_shipping.admin.inc
 *
 */

function commerce_allpay_shipping_settings_form($form, &$form_state){


    $form['allpay_shipping_status']=array(
        '#type' => 'radios',
        '#title'=> '綠界系統狀態',
        '#description'=> '選擇對應的系統狀態。例如：測試環境、正式環境',
        '#options' => array(
            'dev' => '測試環境',
            'production' => '正式環境',
        ),
        '#default_value' => variable_get('allpay_shipping_status','dev'),
        '#required' => TRUE,
        '#weight'=>0,
    );

    $form['allpay_shipping_MerchantID'] = array(
        '#type'=>'textfield',
        '#title'=>'MerchantID',
        '#description'=>'MerchantID商店代號',
        '#maxlength' => 255,
        '#size' => 30,
        '#required' => TRUE,
        '#default_value' => variable_get('allpay_shipping_MerchantID', ALLPAY_SHIPPING_TEST_MERCHANT_ID),
        '#weight'=>1,
    );

    $form['allpay_shipping_HashKey'] = array(
        '#type'=>'textfield',
        '#title'=>'HashKey',
        '#description'=>'allPay提供的HashKey',
        '#maxlength' => 255,
        '#size' => 30,
        '#required' => TRUE,
        '#default_value' => variable_get('allpay_shipping_HashKey', ALLPAY_SHIPPING_TEST_HASHKEY),
        '#weight'=>2,
    );

    $form['allpay_shipping_HashIV'] = array(
        '#type'=>'textfield',
        '#title'=>'HashIV',
        '#description'=>'allPay提供的HashIV',
        '#maxlength' => 255,
        '#size' => 30,
        '#required' => TRUE,
        '#default_value' => variable_get('allpay_shipping_HashIV', ALLPAY_SHIPPING_TEST_HASHIV),
        '#weight'=>3,
    );

    $form['allpay_shipping_sendername'] = array(
        '#type'=>'textfield',
        '#title'=>'寄件人姓名',
        '#description'=>'請務必填寫，請勿填寫公司名稱，避免退貨的時候找不到人',
        '#maxlength' => 255,
        '#size' => 30,
        '#required' => TRUE,
        '#default_value' => variable_get('allpay_shipping_sendername', '王小明'),
        '#weight'=>4,
    );

    $form['allpay_shipping_senderphone'] = array(
        '#type'=>'textfield',
        '#title'=>'寄件人電話',
        '#description'=>'請務必填寫，不要有特殊字元，例如：0227721225即可',
        '#maxlength' => 255,
        '#size' => 30,
        '#required' => TRUE,
        '#default_value' => variable_get('allpay_shipping_senderphone', ''),
        '#weight'=>5,
    );

    $form['allpay_shipping_sendercellphone'] = array(
        '#type'=>'textfield',
        '#title'=>'寄件人手機',
        '#description'=>'請務必填寫,不要有特殊字元，例如：0937123456即可',
        '#maxlength' => 255,
        '#size' => 30,
        '#required' => TRUE,
        '#default_value' => variable_get('allpay_shipping_sendercellphone', ''),
        '#weight'=>6,
    );

    $form['allpay_shipping_zipcode'] = array(
        '#type'=>'textfield',
        '#title'=>'寄件人郵遞區號',
        '#description'=>'請務必填寫',
        '#maxlength' => 255,
        '#size' => 30,
        '#required' => TRUE,
        '#default_value' => variable_get('allpay_shipping_zipcode', ''),
        '#weight'=>7,
    );

    $form['allpay_shipping_address'] = array(
        '#type'=>'textfield',
        '#title'=>'寄件人地址',
        '#description'=>'請務必填寫',
        '#maxlength' => 255,
        '#size' => 60,
        '#required' => TRUE,
        '#default_value' => variable_get('allpay_shipping_address', ''),
        '#weight'=>8,
    );

    $form['allpay_shipping_pickuptime']=array(
        '#type' => 'radios',
        '#title'=> '綠界系統狀態',
        '#description'=> '選擇對應的系統狀態。例如：測試環境、正式環境',
        '#options' => array(
            '1' => '9:00~12:00',
            '2' => '12:00~17:00',
            '3' => '17:00~20:00',
            '4' => '不限時',
        ),
        '#default_value' => variable_get('allpay_shipping_pickuptime',''),
        '#required' => TRUE,
        '#weight'=>9,
    );

    $form['submit']=array(
        '#type'=>'submit',
        '#weight'=>10,
        '#value'=> '儲存',
    );
    return $form;
}

function commerce_allpay_shipping_settings_form_submit($form,&$form_state){

    $allpay_shipping_status = $form_state['values']['allpay_shipping_status'];
    $allpay_shipping_MerchantID = $form_state['values']['allpay_shipping_MerchantID'];
    $allpay_shipping_HashKey = $form_state['values']['allpay_shipping_HashKey'];
    $allpay_shipping_HashIV = $form_state['values']['allpay_shipping_HashIV'];
    $allpay_shipping_sendername = $form_state['values']['allpay_shipping_sendername'];
    $allpay_shipping_senderphone = $form_state['values']['allpay_shipping_senderphone'];
    $allpay_shipping_sendercellphone = $form_state['values']['allpay_shipping_sendercellphone'];
    $allpay_shipping_zipcode = $form_state['values']['allpay_shipping_zipcode'];
    $allpay_shipping_address = $form_state['values']['allpay_shipping_address'];
    $allpay_shipping_pickuptime = $form_state['values']['allpay_shipping_pickuptime'];

    variable_set('allpay_shipping_status',$allpay_shipping_status);
    variable_set('allpay_shipping_MerchantID',$allpay_shipping_MerchantID);
    variable_set('allpay_shipping_HashKey',$allpay_shipping_HashKey);
    variable_set('allpay_shipping_HashIV',$allpay_shipping_HashIV);
    variable_set('allpay_shipping_sendername',$allpay_shipping_sendername);
    variable_set('allpay_shipping_senderphone',$allpay_shipping_senderphone);
    variable_set('allpay_shipping_sendercellphone',$allpay_shipping_sendercellphone);
    variable_set('allpay_shipping_zipcode',$allpay_shipping_zipcode);
    variable_set('allpay_shipping_address',$allpay_shipping_address);
    variable_set('allpay_shipping_pickuptime',$allpay_shipping_pickuptime);
    drupal_set_message('修改更新成功');
}