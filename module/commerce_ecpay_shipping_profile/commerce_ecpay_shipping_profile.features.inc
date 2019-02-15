<?php
/**
 * @file
 * commerce_ecpay_shipping_profile.features.inc
 */

/**
 * Implements hook_commerce_customer_profile_type_info().
 */
function commerce_ecpay_shipping_profile_commerce_customer_profile_type_info() {
  $items = array(
    'recipient' => array(
      'description' => 'The profile used to collect personal information on the checkout and order forms.',
      'help' => '',
      'addressfield' => FALSE,
      'module' => 'commerce_ecpay_shipping_profile',
      'label_callback' => 'commerce_customer_profile_default_label',
      'type' => 'recipient',
      'name' => '收件人資訊',
    ),
  );
  return $items;
}

/**
 * Implements hook_ctools_plugin_api().
 */
function commerce_ecpay_shipping_profile_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
