<?php
/**
 * @file
 * movie_import.admin.inc
 */
// a function to create a admin settings page
function movie_import_admin_form() {
    $form = array();

    $form['movie_import_api_url'] = array(
        '#type' => 'textfield',
        '#title' => t('Movie Importer API'),
        '#default_value' => variable_get('movie_import_api_url'),
        '#required' => TRUE,
        '#size' => 60
    );

    return system_settings_form($form);
}
