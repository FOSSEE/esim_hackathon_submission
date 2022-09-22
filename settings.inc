<?php
// $Id$
function hackathon_submission_settings_form($form, $form_state)
{
	/************************** SoC Marathon date and extension settings **************************/
	$form['extensions']['soc_marathon_literature_report_extensions'] = array(
        '#type' => 'textfield',
        '#title' => t('Allowed file extensions for uploading SoC Marathon Literature report'),
        '#description' => t('A comma separated list WITHOUT SPACE of source file extensions that are permitted to be uploaded on the server'),
        '#size' => 50,
        '#maxlength' => 255,
        '#required' => TRUE,
        '#default_value' => variable_get('soc_marathon_literature_report_extensions', '')
    );
    $form['extensions']['soc_marathon_literature_report_start_date'] = array(
        '#type' => 'textfield',
        '#title' => t('SoC marathon Literature Survey start date'),
        '#description' => t('For eg: 2022-02-28 23:59:59.0, enter in this format'),
        '#size' => 50,
        '#maxlength' => 255,
        '#required' => TRUE,
        '#default_value' => variable_get('soc_marathon_literature_report_start_date', '')
    );
    $form['extensions']['soc_marathon_literature_report_last_date'] = array(
        '#type' => 'textfield',
        '#title' => t('SoC marathon Literature Survey Last date'),
        '#description' => t('For eg: 2022-02-28 23:59:59.0, enter in this format'),
        '#size' => 50,
        '#maxlength' => 255,
        '#required' => TRUE,
        '#default_value' => variable_get('soc_marathon_literature_report_last_date', '')
    );
    /************************* Settings for SoC marathon ends *****************************************/
	$form['extensions']['mscd_literature_report_extensions'] = array(
		'#type' => 'textfield',
		'#title' => t('Allowed file extensions for uploading MSCD Literature report'),
		'#description' => t('A comma separated list WITHOUT SPACE of source file extensions that are permitted to be uploaded on the server'),
		'#size' => 50,
		'#maxlength' => 255,
		'#required' => TRUE,
		'#default_value' => variable_get('mscd_literature_report_extensions', '')
	);
	$form['extensions']['mscd_literature_report_start_date'] = array(
		'#type' => 'textfield',
		'#title' => t('MSCD Literature Survey start date'),
		'#description' => t('For eg: 2022-02-28 23:59:59.0, enter in this format'),
		'#size' => 50,
		'#maxlength' => 255,
		'#required' => TRUE,
		'#default_value' => variable_get('mscd_literature_report_start_date', '')
	);
	$form['extensions']['mscd_literature_report_last_date'] = array(
		'#type' => 'textfield',
		'#title' => t('MSCD Literature Survey Last date'),
		'#description' => t('For eg: 2022-02-28 23:59:59.0, enter in this format'),
		'#size' => 50,
		'#maxlength' => 255,
		'#required' => TRUE,
		'#default_value' => variable_get('mscd_literature_report_last_date', '')
	);
	$form['extensions']['mscd_final_report_extensions'] = array(
		'#type' => 'textfield',
		'#title' => t('Allowed file extensions for uploading MSCD Final report'),
		'#description' => t('A comma separated list WITHOUT SPACE of source file extensions that are permitted to be uploaded on the server'),
		'#size' => 50,
		'#maxlength' => 255,
		'#required' => TRUE,
		'#default_value' => variable_get('mscd_final_report_extensions', '')
	);
	$form['extensions']['mscd_project_files_extensions'] = array(
		'#type' => 'textfield',
		'#title' => t('Allowed file extensions for uploading MSCD Project Files'),
		'#description' => t('A comma separated list WITHOUT SPACE of source file extensions that are permitted to be uploaded on the server'),
		'#size' => 50,
		'#maxlength' => 255,
		'#required' => TRUE,
		'#default_value' => variable_get('mscd_project_files_extensions', '')
	);
	$form['extensions']['mscd_final_submission_start_date'] = array(
		'#type' => 'textfield',
		'#title' => t('MSCD Final start date'),
		'#description' => t('For eg: 2022-02-28 23:59:59.0, enter in this format'),
		'#size' => 50,
		'#maxlength' => 255,
		'#required' => TRUE,
		'#default_value' => variable_get('mscd_final_submission_start_date', '')
	);
	$form['extensions']['mscd_final_submission_last_date'] = array(
		'#type' => 'textfield',
		'#title' => t('MSCD Final Submission Last date'),
		'#description' => t('For eg: 2022-02-28 23:59:59.0, enter in this format'),
		'#size' => 50,
		'#maxlength' => 255,
		'#required' => TRUE,
		'#default_value' => variable_get('mscd_final_submission_last_date', '')
	);
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
	variable_set('soc_marathon_literature_report_extensions', $form_state['values']['soc_marathon_literature_report_extensions']);
	variable_set('soc_marathon_literature_report_start_date', $form_state['values']['soc_marathon_literature_report_start_date']);
	variable_set('soc_marathon_literature_report_last_date', $form_state['values']['soc_marathon_literature_report_last_date']);
	variable_set('mscd_literature_report_extensions', $form_state['values']['mscd_literature_report_extensions']);
	variable_set('mscd_literature_report_start_date', $form_state['values']['mscd_literature_report_start_date']);
	variable_set('mscd_literature_report_last_date', $form_state['values']['mscd_literature_report_last_date']);
	variable_set('mscd_final_report_extensions', $form_state['values']['mscd_final_report_extensions']);
	variable_set('mscd_project_files_extensions', $form_state['values']['mscd_project_files_extensions']);
	variable_set('mscd_final_submission_start_date', $form_state['values']['mscd_final_submission_start_date']);
	variable_set('mscd_final_submission_last_date', $form_state['values']['mscd_final_submission_last_date']);
	variable_set('reference_circuit_extensions', $form_state['values']['reference_circuit']);
	variable_set('reference_waveform_extensions', $form_state['values']['reference_waveform']);
	variable_set('main_netlist_file_extensions', $form_state['values']['main_netlist']);
	variable_set('subcircuit_file_extensions', $form_state['values']['sub_circuit_file']);
	variable_set('readme_file_extensions', $form_state['values']['read_me']);
	drupal_set_message(t('Settings updated'), 'status');
}
