<?php
/**
 * @file
 * commerce_ecpay_shipping_profile.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function commerce_ecpay_shipping_profile_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_commerce_customer_profile__recipient';
  $strongarm->value = array(
    'view_modes' => array(
      'administrator' => array(
        'custom_settings' => FALSE,
      ),
      'customer' => array(
        'custom_settings' => FALSE,
      ),
      'addressbook' => array(
        'custom_settings' => FALSE,
      ),
      'diff_standard' => array(
        'custom_settings' => FALSE,
      ),
      'ief_table' => array(
        'custom_settings' => FALSE,
      ),
      'token' => array(
        'custom_settings' => FALSE,
      ),
    ),
    'extra_fields' => array(
      'form' => array(),
      'display' => array(
        'flag_profile_default' => array(
          'default' => array(
            'weight' => '14',
            'visible' => FALSE,
          ),
        ),
      ),
    ),
  );
  $export['field_bundle_settings_commerce_customer_profile__recipient'] = $strongarm;

  return $export;
}
