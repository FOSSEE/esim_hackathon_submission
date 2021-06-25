<?php
// $Id$
function hackathon_submission_settings_form($form, $form_state)
{
	/*$form['bcc_emails'] = array(
		'#type' => 'textfield',
		'#title' => t('(Bcc) Notification emails'),
		'#description' => t('Specify emails id for Bcc option of mail system with comma separated'),
		'#size' => 50,
		'#maxlength' => 255,
		'#required' => TRUE,
		'#default_value' => variable_get('hackathon_submission_bcc_emails', '')
	);
	$form['cc_emails'] = array(
		'#type' => 'textfield',
		'#title' => t('(Cc) Notification emails'),
		'#description' => t('Specify emails id for Cc option of mail system with comma separated'),
		'#size' => 50,
		'#maxlength' => 255,
		'#required' => TRUE,
		'#default_value' => variable_get('hackathon_submission_cc_emails', '')
	);
	$form['from_email'] = array(
		'#type' => 'textfield',
		'#title' => t('Outgoing from email address'),
		'#description' => t('Email address to be display in the from field of all outgoing messages'),
		'#size' => 50,
		'#maxlength' => 255,
		'#required' => TRUE,
		'#default_value' => variable_get('hackathon_submission_from_email', '')
	);*/
	$form['extensions']['reference_circuit'] = array(
		'#type' => 'textfield',
		'#title' => t('Allowed file extensions for uploading reference circuit file'),
		'#description' => t('A comma separated list WITHOUT SPACE of source file extensions that are permitted to be uploaded on the server'),
		'#size' => 50,
		'#maxlength' => 255,
		'#required' => TRUE,
		'#default_value' => variable_get('reference_circuit_extensions', '')
	);
	$form['extensions']['reference_waveform'] = array(
		'#type' => 'textfield',
		'#title' => t('Allowed file extensions for uploading reference waveform file'),
		'#description' => t('A comma separated list WITHOUT SPACE of source file extensions that are permitted to be uploaded on the server'),
		'#size' => 50,
		'#maxlength' => 255,
		'#required' => TRUE,
		'#default_value' => variable_get('reference_waveform_extensions', '')
	);
	$form['extensions']['main_netlist'] = array(
		'#type' => 'textfield',
		'#title' => t('Allowed file extensions for uploading Main netlist file'),
		'#description' => t('A comma separated list WITHOUT SPACE of source file extensions that are permitted to be uploaded on the server'),
		'#size' => 50,
		'#maxlength' => 255,
		'#required' => TRUE,
		'#default_value' => variable_get('main_netlist_file_extensions', '')
	);
	$form['extensions']['sub_circuit_file'] = array(
		'#type' => 'textfield',
		'#title' => t('Allowed file extensions for uploading sub circuit file'),
		'#description' => t('A comma separated list WITHOUT SPACE of source file extensions that are permitted to be uploaded on the server'),
		'#size' => 50,
		'#maxlength' => 255,
		'#required' => TRUE,
		'#default_value' => variable_get('subcircuit_file_extensions', '')
	);
	$form['extensions']['read_me'] = array(
		'#type' => 'textfield',
		'#title' => t('Allowed file extensions for uploading Read me file'),
		'#description' => t('A comma separated list WITHOUT SPACE of source file extensions that are permitted to be uploaded on the server'),
		'#size' => 50,
		'#maxlength' => 255,
		'#required' => TRUE,
		'#default_value' => variable_get('readme_file_extensions', '')
	);
	/*$form['no_of_images_allowed_project_submission'] = array(
		'#type' => 'textfield',
		'#title' => t('Enter the number of images that can be uploaded during project submission'),
		'#size' => 50,
		'#default_value' => variable_get('no_of_images_allowed_project_submission', '')
	);
	$form['extensions']['project_design_files'] = array(
		'#type' => 'textfield',
		'#title' => t('Allowed file extensions for uploading project design files'),
		'#description' => t('A comma separated list WITHOUT SPACE of source file extensions that are permitted to be uploaded on the server'),
		'#size' => 50,
		'#maxlength' => 255,
		'#required' => TRUE,
		'#default_value' => variable_get('project_design_files_extensions', '')
	);*/
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Submit')
	);
	return $form;
}
function hackathon_submission_settings_form_validate($form, &$form_state)
{
	return;
}
function hackathon_submission_settings_form_submit($form, &$form_state)
{
	/*variable_set('hackathon_submission_bcc_emails', $form_state['values']['bcc_emails']);
	variable_set('hackathon_submission_cc_emails', $form_state['values']['cc_emails']);
	variable_set('hackathon_submission_from_email', $form_state['values']['from_email']);
	*/variable_set('reference_circuit_extensions', $form_state['values']['reference_circuit']);
	variable_set('reference_waveform_extensions', $form_state['values']['reference_waveform']);
	variable_set('main_netlist_file_extensions', $form_state['values']['main_netlist']);
	variable_set('subcircuit_file_extensions', $form_state['values']['sub_circuit_file']);
	variable_set('readme_file_extensions', $form_state['values']['read_me']);
	drupal_set_message(t('Settings updated'), 'status');
}
