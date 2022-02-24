<?php

function edit_literature_report_submission_form($form, $form_state, $no_js_use = FALSE){
    global $user;
    $submission_id = arg(3);
    if ($user->uid == 0)
    {
        $msg = drupal_set_message(t('It is mandatory to log in on this website to edit your submission. If you are new user please create a new account first.'), 'error');
        //drupal_goto('esim-circuit-simulation-project');
        drupal_goto('user/login', array('query' => drupal_get_destination()));
        return $msg;
    } //$user->uid == 0
    $query = db_select('hackathon_literature_survey');
    $query->fields('hackathon_literature_survey');
    $query->condition('uid', $user->uid);
    $query->condition('id', $submission_id);
    //$query->range(0, 1);
    $submission_q = $query->execute();
    $submission_data = $submission_q->fetchObject();
    $form = array();
    $form['participant_name'] = array(
        '#title' => t('Participant Name'),
        '#type' => 'textfield',
        '#disabled' => TRUE,
        '#size' => 70,
        '#maxlength' => 70,
        '#default_value' => $submission_data->participant_name
    );
    $form['participant_email'] = array(
        '#type' => 'textfield',
        '#title' => t('Email'),
        '#size' => 30,
        '#value' => $user->mail,
        '#disabled' => TRUE
    );
    $form['institute'] = array(
        '#type' => 'textfield',
        '#title' => t('Name of the college/institute'),
        '#disabled' => TRUE,
        '#size' => 70,
        '#maxlength' => 70,
        '#required' => TRUE,
        '#default_value' => $submission_data->institute
    );
   /* $form['circuit'] = array(
        '#type' => 'fieldset',
        '#title' => t('Circuits'),
        '#collapsible' => FALSE,
        '#collapsed' => FALSE
    );*/
    $form['circuit_name'] = array(
        '#title' => t('Circuit Name'),
        '#type' => 'textfield',
        '#size' => 70,
        '#maxlength' => 70,
        '#required' => TRUE,
        '#default_value' => $submission_data->circuit_name
    );
    $form['abstract'] = array(
        '#title' => t('Abstract'),
        '#type' => 'textarea',
        '#description' => t('The abstract should contain minimum 600 characters and not exceed more than 725 characters'),
        '#rows' => 5,
        '#minlength' => 600,
        '#maxlength' => 725,
        '#required' => TRUE,
        '#default_value' => $submission_data->abstract
        /*'#ajax' => array(
        'callback' => 'update_length_ajax_callback',
        'wrapper' => 'length-div',
        'method' => 'replace',
        'effect' => 'fade',
        ),*/
    );
    $form['circuit_details'] = array(
        '#title' => t('Circuit Details'),
        '#type' => 'textarea',
        '#description' => t('The circuit details should contain minimum 1334 characters and not exceed more than 1600 characters'),
        '#rows' => 5,
        '#minlength' => 1334,
        '#maxlength' => 1600,
        '#required' => TRUE,
        '#default_value' => $submission_data->circuit_details
    );    
    $form['reference_files'] = array(
        '#type' => 'fieldset',
        '#title' => t('Upload Reference Files'),
        '#collapsible' => FALSE,
        '#collapsed' => FALSE
    );
    //var_dump($submission_id);die;
    $existing_uploaded_C_file = default_value_for_uploaded_reference_files("C", $submission_id);
    //var_dump($existing_uploaded_C_file);die;
    if (!$existing_uploaded_C_file)
    {
        $existing_uploaded_C_file = new stdClass();
        $existing_uploaded_C_file->filename = "No file uploaded";
    }
    $form['reference_files']['reference_circuit'] = array(
        '#type' => 'file',
        '#title' => t('Upload reference circuit'),
        '#size' => 48,
        '#upload_validators' => array(
                'file_validate_extensions' => array(variable_get('reference_circuit_extensions', '')),
                // Pass the maximum file size in bytes
                /*'file_validate_size' => array(5*1024*1024),*/
              ),
        '#description' => t('Upload image(900x600 pixels) with allowed extensions only. No spaces or any special characters allowed in filename.') . '<br />' . t('<span style="color:red;">Current File :</span> ') . $existing_uploaded_C_file->filename . '<br />' . t('<span style="color:red;">Allowed file extensions: ') . variable_get('reference_circuit_extensions', '') . '</span>'
    );
    $existing_uploaded_W_file = default_value_for_uploaded_reference_files("W", $submission_id);
    if (!$existing_uploaded_W_file)
    {
        $existing_uploaded_W_file = new stdClass();
        $existing_uploaded_W_file->filename = "No file uploaded";
    }
    $form['reference_files']['reference_waveform'] = array(
        '#type' => 'file',
        '#title' => t('Upload reference waveform'),
        '#size' => 48,
        '#upload_validators' => array(
                'file_validate_extensions' => array(variable_get('reference_circuit_extensions', '')),
                // Pass the maximum file size in bytes
                /*'file_validate_size' => array(5*1024*1024),*/
              ),
        '#description' => t('Upload image(900x600 pixels) with allowed extensions only. No spaces or any special characters allowed in filename.') . '<br />' . t('<span style="color:red;">Current File :</span> ') . $existing_uploaded_W_file->filename . '<br />' . t('<span style="color:red;">Allowed file extensions: ') . variable_get('reference_waveform_extensions', '') . '</span>'
    );
    $query_bib_ref = db_select('hackathon_literature_survey_bib_references');
    $query_bib_ref->fields('hackathon_literature_survey_bib_references');
    $query_bib_ref->condition('submission_id', $submission_id);
    $result_bib_ref = $query_bib_ref->execute();
    $num_of_fellowresults = $result_bib_ref->rowCount();
    //var_dump($num_of_bib_ref);die;
    $form['existing_bib_reference_fieldset'] = array(
            '#type' => 'fieldset',
            '#title' => t('References'),
            '#tree' => TRUE,
            '#prefix' => '<div id="existing_bib_reference-fieldset-wrapper">',
            '#suffix' => '</div>'
    ); 
    $i = 0;
            while ($row_s = $result_bib_ref->fetchObject()) {
            	
                $temp = $i;
                $form['existing_bib_reference_fieldset'][$i]["s_text"] = array(
                    "#type" => "item",
                    "#markup" => "<h4><label>Resource : " . ($temp + 1) . "</label></h4>"
                );
                $form['existing_bib_reference_fieldset'][$i]["id"] = array(
                    "#type" => "hidden",
                    "#default_value" => $row_s->id
                );
                $form['existing_bib_reference_fieldset'][$i]["resource_link"] = array(
                    "#type" => "textfield",
                    "#title" => "Resource Link",
                    "#default_value" => $row_s->resource_link
                );
                $form['existing_bib_reference_fieldset'][$i]["resource_title"] = array(
                    "#type" => "textfield",
                    "#title" => "Resource Title",
                    "#default_value" => $row_s->resource_title
                );
                $form['existing_bib_reference_fieldset'][$i]["resource_author"] = array(
                    "#type" => "textfield",
                    "#title" => "Resource Author",
                    "#default_value" => $row_s->resource_author
                );
                $i++;
            }
    $form['bib_reference_fieldset'] = array(
            '#type' => 'fieldset',
            '#title' => t('References'),
            '#tree' => TRUE,
            '#prefix' => '<div id="bib_reference-fieldset-wrapper">',
            '#suffix' => '</div>'
        );         
          /*  if (empty($form_state['num_bib_reference'])) {
                $form_state['num_bib_reference'] = 1;
            }*/
            $temp = 0;
            for ($i = $num_of_fellowresults; $i < 3; $i++) {
                $temp = $i;
                $form['bib_reference_fieldset'][$i]["s_text"] = array(
                    "#type" => "item",
                    "#markup" => "<h4><label>Reference: " . ($temp + 1) . "</label></h4>"
                );
                $form['bib_reference_fieldset'][$i]["resource_link"] = array(
                    "#type" => "textfield",
                    "#title" => "Link to the resource",
                    "#default_value" => "",
                    
                );
                $form['bib_reference_fieldset'][$i]["resource_title"] = array(
                    "#type" => "textfield",
                    "#title" => "Resource Paper title",
                    "#default_value" => "",
                    
                );
                $form['bib_reference_fieldset'][$i]["resource_author"] = array(
                    "#type" => "textfield",
                    "#title" => "Author of the resource",
                    "#default_value" => "",
                    
                );
               
            }
            $form["bib_reference_count"] = array(
                "#type" => "hidden",
                "#value" => $num_of_fellowresults
            );
            /*if($i <3){
            $form['bib_reference_fieldset']['add_bib_reference'] = array(
                '#type' => 'submit',
                '#value' => t('Add more'),
                '#limit_validation_errors' => array(),
                '#submit' => array(
                    'edit_form_bib_reference_add_more_add_one'
                ),
                '#ajax' => array(
                    'callback' => 'edit_form_bib_reference_add_more_callback',
                    'wrapper' => 'bib_reference-fieldset-wrapper'
                )
            );
        }
            if ($form_state['num_bib_reference'] > 1) {
                $form['bib_reference_fieldset']['remove_bib_reference'] = array(
                    '#type' => 'submit',
                    '#value' => t('Remove'),
                    '#limit_validation_errors' => array(),
                    '#submit' => array(
                        'edit_form_bib_reference_add_more_remove_one'
                    ),
                    '#ajax' => array(
                        'callback' => 'bib_reference_add_more_callback',
                        'wrapper' => 'bib_reference-fieldset-wrapper'
                    )
                );
            }
            if ($no_js_use) {
                if (!empty($form['bib_reference_fieldset']['remove_bib_reference']['#ajax'])) {
                    unset($form['bib_reference_fieldset']['remove_bib_reference']['#ajax']);
                }
                unset($form['bib_reference_fieldset']['add_bib_reference']['#ajax']);
            }*/

    $form["submit"] = array(
        "#type" => "submit",
    '#weight' => '6',
        "#value" => "Submit"
    );
    return $form;
}
/*function edit_form_bib_reference_add_more_callback($form, $form_state) {
    return $form['bib_reference_fieldset'];
}


function edit_form_bib_reference_add_more_add_one($form, &$form_state) {
	if (!isset($form_state['num_bib_reference'])) {
        $form_state['num_bib_reference'] = 0;
        $form_state['num_bib_reference']++;
    }

    $form_state['num_bib_reference']++;
    $form_state['rebuild'] = TRUE;
    //$form_state['no_redirect'] = TRUE;
}


function edit_form_bib_reference_add_more_remove_one($form, &$form_state) {
    if ($form_state['num_bib_reference'] > 1) {
        $form_state['num_bib_reference']--;
    }
    $form_state['rebuild'] = TRUE;
}*/



function edit_literature_report_submission_form_validate($form, &$form_state){
	if (strlen($form_state['values']['abstract']) < 600)
        {
            form_set_error('abstract', t('Minimum charater limit for abstract is 600 charaters'));
        }
    if (strlen($form_state['values']['circuit_details']) < 1334)
        {
            form_set_error('circuit_details', t('Minimum charater limit for circuit details is 1334 charaters'));
        }
    if (isset($_FILES['files']))
    {
        /* check if atleast one source or result file is uploaded */
        /*if (!($_FILES['files']['name']['reference_circuit']))
            form_set_error('reference_circuit', t('Please upload the circuit diagram'));
        if(!($_FILES['files']['name']['reference_waveform']))
            form_set_error('reference_waveform', t('Please upload the waveform'));*/
        /* check for valid filename extensions */
        foreach ($_FILES['files']['name'] as $file_form_name => $file_name)
        {
            if ($file_name)
            {
                /* checking file type */
                if (strstr($file_form_name, 'reference_circuit'))
                        $file_type = 'C';
                else if (strstr($file_form_name, 'reference_waveform'))
                        $file_type = 'W';
                $allowed_extensions_str = '';
                switch ($file_type)
                {
                    case 'C':
                        $allowed_extensions_str = variable_get('reference_circuit_extensions', '');
                        break;
                    case 'W':
                        $allowed_extensions_str = variable_get('reference_waveform_extensions', '');
                        break;
                }
                $allowed_extensions = explode(',', $allowed_extensions_str);
                $fnames = explode('.', strtolower($_FILES['files']['name'][$file_form_name]));
                $temp_extension = end($fnames);
                if (!in_array($temp_extension, $allowed_extensions))
                    form_set_error($file_form_name, t('Only file with ' . $allowed_extensions_str . ' extensions can be uploaded.'));
                if ($_FILES['files']['size'][$file_form_name] <= 0)
                    form_set_error($file_form_name, t('File size cannot be zero.'));
                /* check if valid file name */
                if (!hackathon_submission_check_valid_filename($_FILES['files']['name'][$file_form_name]))
                    form_set_error($file_form_name, t('Invalid file name specified. Only alphabets and numbers are allowed as a valid filename.'));
            } //$file_name
        } //$_FILES['files']['name'] as $file_form_name => $file_name
    } 
    return $form_state;
}



function edit_literature_report_submission_form_submit($form, $form_state){
	$submission_id = arg(3);
	global $user;
	$v = $form_state['values'];
	$root_path = hackathon_submission_files_path();
	$query = "UPDATE hackathon_literature_survey SET 
				circuit_name = :circuit_name,
				abstract=:abstract,
				circuit_details=:circuit_details
				WHERE id=:submission_id";
	$args = array(
		":circuit_name" => $v['circuit_name'],
		':abstract' => $v['abstract'],
		':circuit_details' => $v['circuit_details'],
		':submission_id' => $submission_id
	);
	$result = db_query($query, $args);
	/*$submission_id = db_query($query, $args, array(
        'return' => Database::RETURN_INSERT_ID
    ));*/
    $query = db_select('hackathon_literature_survey');
    $query->fields('hackathon_literature_survey');
    $query->condition('uid', $user->uid);
    $query->condition('id', $submission_id);
    $query->range(0, 1);
    $proposal_q = $query->execute();
    $proposal_data = $proposal_q->fetchObject();
    $proposal_dir_path = $proposal_data->directory_name . '/';
    $dest_path1 = $proposal_dir_path . 'literature_survey/';
    $dest_path = $dest_path1 . 'reference_files/';
    $bib_reference_upload = 0;
            for ($i = 0; $i < 3; $i++) {
                //$f_id=$v['bib_reference_fieldset'][$i]["f_id"];
                if ($v['bib_reference_fieldset'][$i]["resource_link"] != "") {
                    $bib_referencequery = "INSERT INTO hackathon_literature_survey_bib_references (submission_id,resource_link,resource_title,resource_author) VALUES (:submission_id,:resource_link,:resource_title,:resource_author)";
                    $bib_referenceargs = array(
                        ":submission_id" => $submission_id,
                        ":resource_link" => trim($v['bib_reference_fieldset'][$i]["resource_link"]),
                        ":resource_title" => trim($v['bib_reference_fieldset'][$i]["resource_title"]),
                        ":resource_author" => trim($v['bib_reference_fieldset'][$i]["resource_author"])
                    );
                    /* storing the row id in $result */
                    $bib_referenceresult = db_query($bib_referencequery, $bib_referenceargs, array(
                        'return' => Database::RETURN_INSERT_ID
                    ));
                    if ($bib_referenceresult != 0) {
                        $bib_reference_upload++;
                    }
                }
            }
    $existing_bib_reference_upload = 0;
            for ($i = 0; $i <= $v["bib_reference_count"]; $i++) {
                //$f_id=$v['bib_reference_fieldset'][$i]["f_id"];
                //if ($v['existing_bib_reference_fieldset'][$i]["resource_link"] != "") {
                    $bib_referencequery = "UPDATE hackathon_literature_survey_bib_references set
                    resource_link = :resource_link,
                    resource_title = :resource_title,
                    resource_author = :resource_author
                    WHERE id =:id";
                    $bib_referenceargs = array(
                        ":resource_link" => trim($v['existing_bib_reference_fieldset'][$i]["resource_link"]),
                        ":resource_title" => trim($v['existing_bib_reference_fieldset'][$i]["resource_title"]),
                        ":resource_author" => trim($v['existing_bib_reference_fieldset'][$i]["resource_author"]),
                        ":id" => $v['existing_bib_reference_fieldset'][$i]["id"]
                    );
                    /* storing the row id in $result */
                    $bib_referenceresult = db_query($bib_referencequery, $bib_referenceargs);
                    if ($bib_referenceresult != 0) {
                        $existing_bib_reference_upload++;
                    }
                //}
            }

	foreach ($_FILES['files']['name'] as $file_form_name => $file_name)
    {
        if ($file_name)
        {
            /* checking file type */
            if (strstr($file_form_name, 'reference_circuit'))
            {
                $file_type = 'C';
            } //strstr($file_form_name, 'upload_circuit_simulation_developed_process')
            else if (strstr($file_form_name, 'reference_waveform'))
            {
                $file_type = 'W';
            } 
            switch ($file_type)
            {
                case 'C':
                    if (file_exists($root_path . $dest_path . $_FILES['files']['name'][$file_form_name]))
                    {
                         drupal_set_message(t("Error uploading file. File !filename already exists.", array('!filename' => $_FILES['files']['name'][$file_form_name])), 'error');
                        //unlink($root_path . $dest_path . $_FILES['files']['name'][$file_form_name]);
                    } //file_exists($root_path . $dest_path . $_FILES['files']['name'][$file_form_name])
                    /* uploading file */
                    else if (move_uploaded_file($_FILES['files']['tmp_name'][$file_form_name], $root_path . $dest_path . $_FILES['files']['name'][$file_form_name]))
                    {
                    	$query_ab_f = "SELECT * FROM hackathon_literature_survey_files WHERE submission_id = :submission_id AND filetype = 
				:filetype";
						$args_ab_f = array(
							":submission_id" => $submission_id,
							":filetype" => $file_type
						);
						$query_ab_f_result = db_query($query_ab_f, $args_ab_f)->fetchObject();
						unlink($root_path . $dest_path . $query_ab_f_result->filename);
                        $query = "UPDATE {hackathon_literature_survey_files} set 
                         filename = :filename, 
                         filepath = :filepath,
                         filemime = :filemime,
                         filesize = :filesize
                         WHERE submission_id = :submission_id and filetype = :filetype";
                            $args = array(
                                ":filename" => $_FILES['files']['name'][$file_form_name],
                                ":filepath" => $dest_path . $_FILES['files']['name'][$file_form_name],
                                ":filemime" => mime_content_type($root_path . $dest_path . $_FILES['files']['name'][$file_form_name]),
                                ":filesize" => $_FILES['files']['size'][$file_form_name],
                                ":submission_id" => $submission_id,
                                "filetype" => $file_type
                            );
                        $updateresult = db_query($query, $args);
                        drupal_set_message($file_name . ' uploaded successfully.', 'status');
                    } //move_uploaded_file($_FILES['files']['tmp_name'][$file_form_name], $root_path . $dest_path . $_FILES['files']['name'][$file_form_name])
                    else
                    {
                        drupal_set_message('Error uploading file : ' . $dest_path . $file_name, 'error');
                    }
                    break;
                case 'W':
                    if (file_exists($root_path . $dest_path . $_FILES['files']['name'][$file_form_name]))
                    {
                         drupal_set_message(t("Error uploading file. File !filename already exists.", array('!filename' => $_FILES['files']['name'][$file_form_name])), 'error');
                        //unlink($root_path . $dest_path . $_FILES['files']['name'][$file_form_name]);
                    } //file_exists($root_path . $dest_path . $_FILES['files']['name'][$file_form_name])
                    /* uploading file */
                    else if (move_uploaded_file($_FILES['files']['tmp_name'][$file_form_name], $root_path . $dest_path . $_FILES['files']['name'][$file_form_name]))
                    {
                    	$query_ab_f = "SELECT * FROM hackathon_literature_survey_files WHERE submission_id = :submission_id AND filetype = 
				:filetype";
						$args_ab_f = array(
							":submission_id" => $submission_id,
							":filetype" => $file_type
						);
						$query_ab_f_result = db_query($query_ab_f, $args_ab_f)->fetchObject();
						unlink($root_path . $dest_path . $query_ab_f_result->filename);
                        $query = "UPDATE {hackathon_literature_survey_files} set 
                         filename = :filename, 
                         filepath = :filepath,
                         filemime = :filemime,
                         filesize = :filesize
                         WHERE submission_id = :submission_id and filetype = :filetype";
                            $args = array(
                                ":filename" => $_FILES['files']['name'][$file_form_name],
                                ":filepath" => $dest_path . $_FILES['files']['name'][$file_form_name],
                                ":filemime" => mime_content_type($root_path . $dest_path . $_FILES['files']['name'][$file_form_name]),
                                ":filesize" => $_FILES['files']['size'][$file_form_name],
                                ":submission_id" => $submission_id,
                                "filetype" => $file_type
                            );
                        $updateresult = db_query($query, $args);
                        drupal_set_message($file_name . ' uploaded successfully.', 'status');
                    } //move_uploaded_file($_FILES['files']['tmp_name'][$file_form_name], $root_path . $dest_path . $_FILES['files']['name'][$file_form_name])
                    else
                    {
                        drupal_set_message('Error uploading file : ' . $dest_path . $file_name, 'error');
                    }
                    break;
            }

        }
    }
    drupal_set_message('Updated successfully', 'status'); 
    drupal_goto('hackathon-submission/proposed');
}

function default_value_for_uploaded_reference_files($filetype, $submission_id)
{
    $filetype = $filetype;
    $submission_id = $submission_id;
    $query = db_select('hackathon_literature_survey_files');
    $query->fields('hackathon_literature_survey_files');
    $query->condition('submission_id', $submission_id);
    $selected_files_array = "";
    if ($filetype == "C")
    {
        $query->condition('filetype', $filetype);
        $filetype_q = $query->execute()->fetchObject();
        return $filetype_q;
        //var_dump($filetype_q);die;
    } //$filetype == "A"
    elseif ($filetype == "W")
    {
        $query->condition('filetype', $filetype);
        $filetype_q = $query->execute()->fetchObject();
        return $filetype_q;
    }
    else
    {
        return;
    }
    return;
}


function edit_submission_details_form($form, $form_state, $no_js_use = FALSE){
    global $user;
    $submission_id = arg(3);
    if ($user->uid == 0)
    {
        $msg = drupal_set_message(t('It is mandatory to log in on this website to edit your submission. If you are new user please create a new account first.'), 'error');
        //drupal_goto('esim-circuit-simulation-project');
        drupal_goto('user/login', array('query' => drupal_get_destination()));
        return $msg;
    } //$user->uid == 0
    $query = db_select('hackathon_literature_survey');
    $query->fields('hackathon_literature_survey');
    //$query->condition('uid', $user->uid);
    $query->condition('id', $submission_id);
    //$query->range(0, 1);
    $submission_q = $query->execute();
    $submission_data = $submission_q->fetchObject();
    $form = array();
    $form['participant_name'] = array(
        '#title' => t('Participant Name'),
        '#type' => 'textfield',
        '#size' => 70,
        '#maxlength' => 70,
        '#default_value' => $submission_data->participant_name
    );
    $form['participant_email'] = array(
        '#type' => 'textfield',
        '#title' => t('Email'),
        '#size' => 30,
        '#value' => $user->mail,
        '#disabled' => TRUE
    );
    $form['institute'] = array(
        '#type' => 'textfield',
        '#title' => t('Name of the college/institute'),
        '#size' => 70,
        '#maxlength' => 70,
        '#required' => TRUE,
        '#default_value' => $submission_data->institute
    );
    $form['circuit_name'] = array(
        '#title' => t('Circuit Name'),
        '#type' => 'textfield',
        '#size' => 70,
        '#maxlength' => 70,
        '#required' => TRUE,
        '#default_value' => $submission_data->circuit_name
    );
    $form['abstract'] = array(
        '#title' => t('Abstract'),
        '#type' => 'textarea',
        '#description' => t('The abstract should contain minimum 600 characters and not exceed more than 725 characters'),
        '#rows' => 5,
        '#minlength' => 600,
        '#maxlength' => 725,
        '#required' => TRUE,
        '#default_value' => $submission_data->abstract,
        '#disabled' => TRUE
        /*'#ajax' => array(
        'callback' => 'update_length_ajax_callback',
        'wrapper' => 'length-div',
        'method' => 'replace',
        'effect' => 'fade',
        ),*/
    );
    $form['circuit_details'] = array(
        '#title' => t('Circuit Details'),
        '#type' => 'textarea',
        '#description' => t('The circuit details should contain minimum 1334 characters and not exceed more than 1600 characters'),
        '#rows' => 5,
        '#minlength' => 1334,
        '#maxlength' => 1600,
        '#required' => TRUE,
        '#default_value' => $submission_data->circuit_details,
        '#disabled' => TRUE
    );   

    $form["submit"] = array(
        "#type" => "submit",
    '#weight' => '6',
        "#value" => "Submit"
    );
    return $form;
}

function edit_submission_details_form_submit($form, $form_state){
    $submission_id = arg(3);
    global $user;
    $v = $form_state['values'];
    $query = "UPDATE hackathon_literature_survey SET 
                circuit_name = :circuit_name,
                participant_name=:participant_name,
                institute=:institute
                WHERE id=:submission_id";
    $args = array(
        ":circuit_name" => $v['circuit_name'],
        ':participant_name' => $v['participant_name'],
        ':institute' => $v['institute'],
        ':submission_id' => $submission_id
    );
    $result = db_query($query, $args);
    drupal_set_message('Updated successfully', 'status'); 
    drupal_goto('hackathon-submission/all-submissions');
}


function edit_mscd_literature_report_submission_form($form, $form_state, $no_js_use = FALSE){
    global $user;
    $submission_id = arg(3);    
    if ($user->uid == 0)
    {
        $msg = drupal_set_message(t('It is mandatory to log in on this website to edit your submission. If you are new user please create a new account first.'), 'error');
        //drupal_goto('esim-circuit-simulation-project');
        drupal_goto('user/login', array('query' => drupal_get_destination()));
        return $msg;
    } //$user->uid == 0
    $query = db_select('mixed_signal_marathon_literature_survey');
    $query->fields('mixed_signal_marathon_literature_survey');
    $query->condition('uid', $user->uid);
    $query->condition('id', $submission_id);
    //$query->range(0, 1);
    $submission_q = $query->execute();
    $submission_data = $submission_q->fetchObject();
    $form = array();
    $form['participant_name'] = array(
        '#title' => t('Participant Name'),
        '#type' => 'textfield',
        '#size' => 70,
        '#maxlength' => 70,
        '#default_value' => $submission_data->participant_name
    );
    $form['participant_email'] = array(
        '#type' => 'textfield',
        '#title' => t('Email'),
        '#size' => 30,
        '#value' => $user->mail,
        '#disabled' => TRUE
    );
    $form['institute'] = array(
        '#type' => 'textfield',
        '#title' => t('Name of the college/institute'),
        '#size' => 70,
        '#maxlength' => 70,
        '#required' => TRUE,
        '#default_value' => $submission_data->institute
    );
    $form['circuit_name'] = array(
        '#title' => t('Circuit Name'),
        '#type' => 'textfield',
        '#size' => 70,
        '#maxlength' => 70,
        '#required' => TRUE,
        '#default_value' => $submission_data->circuit_name
    );
    $form['circuit_type'] = array(
        '#title' => t('Circuit Type'),
        '#type' => 'select',
        '#title' => t('Type of the circuit'),
        '#options' => array(
            'Analog' => 'Analog',
            'Digital' => 'Digital',
            'Mixed' => 'Mixed'
            ),
        '#required' => TRUE,
        '#default_value' => $submission_data->circuit_type
    );    
    $form['reference_files'] = array(
        '#type' => 'fieldset',
        '#title' => t('Edit literature report'),
        '#collapsible' => FALSE,
        '#collapsed' => FALSE
    );
    if(!$submission_data->report_file){
        $report_file = "Not Uploaded";
    }
    else{
        $report_file = $submission_data->report_file;
    }
    $form['reference_files']['literature_report'] = array(
        '#type' => 'file',
        '#size' => 48,
        '#title' => t('Click <a href= "https://static.fossee.in/esim/resources/Literature-survey.pdf" target="_blank">here</a> to view the template of the file.'),
        '#upload_validators' => array(
                'file_validate_extensions' => array(variable_get('mscd_literature_report_extensions', '')),
                // Pass the maximum file size in bytes
                /*'file_validate_size' => array(5*1024*1024),*/
              ),
        '#description' => t('No spaces or any special characters allowed in filename.') . '<br />' . t('<span style="color:red;">Current File:</span> ') . $report_file . '<br />' . t('<span style="color:red;">Allowed file extensions: ') . variable_get('mscd_literature_report_extensions', '') . '</span>'
    );

    $form["submit"] = array(
        "#type" => "submit",
    '#weight' => '6',
        "#value" => "Submit"
    );
    return $form;
}



function edit_mscd_literature_report_submission_form_validate($form, &$form_state){
    if (isset($_FILES['files']))
    {
        /* check if atleast one source or result file is uploaded */
       /* if (!($_FILES['files']['name']['literature_report']))
            form_set_error('literature_report', t('Please upload the literature report'));
       */ /* check for valid filename extensions */
        foreach ($_FILES['files']['name'] as $file_form_name => $file_name)
        {
            if ($file_name)
            {
                /* checking file type */
                /*if (strstr($file_form_name, 'literature_report'))
                        $file_type = 'L';
                $allowed_extensions_str = '';
                switch ($file_type)
                {
                    case 'L':
                        $allowed_extensions_str = variable_get('mscd_literature_report_extensions', '');
                        break;
                }
                $allowed_extensions = explode(',', $allowed_extensions_str);
                $fnames = explode('.', strtolower($_FILES['files']['name'][$file_form_name]));
                $temp_extension = end($fnames);
                if (!in_array($temp_extension, $allowed_extensions))
                    form_set_error($file_form_name, t('Only file with ' . $allowed_extensions_str . ' extensions can be uploaded.'));*/
                if ($_FILES['files']['size'][$file_form_name] <= 0)
                    form_set_error($file_form_name, t('File size cannot be zero.'));
                /* check if valid file name */
                if (!hackathon_submission_check_valid_filename($_FILES['files']['name'][$file_form_name]))
                    form_set_error($file_form_name, t('Invalid file name specified. Only alphabets and numbers are allowed as a valid filename.'));
            } //$file_name
        } //$_FILES['files']['name'] as $file_form_name => $file_name
    }
    return $form_state;
}



function edit_mscd_literature_report_submission_form_submit($form, $form_state){
    $submission_id = arg(3);
    global $user;
    $v = $form_state['values'];
    $root_path = mscd_hackathon_submission_files_path();
    $query = "UPDATE mixed_signal_marathon_literature_survey SET 
                participant_name = :participant_name,
                institute = :institute,
                circuit_name = :circuit_name,
                circuit_type=:circuit_type
                WHERE id=:submission_id";
    $args = array(
        ":participant_name" => $v['participant_name'],
        ":institute" => $v['institute'],
        ":circuit_name" => $v['circuit_name'],
        ":circuit_type" => $v['circuit_type'],
        ":submission_id" => $submission_id
    );
    $result = db_query($query, $args);
    /*$submission_id = db_query($query, $args, array(
        'return' => Database::RETURN_INSERT_ID
    ));*/
    $query = db_select('mixed_signal_marathon_literature_survey');
    $query->fields('mixed_signal_marathon_literature_survey');
    $query->condition('uid', $user->uid);
    $query->condition('id', $submission_id);
    //$query->range(0, 1);
    $submission_q = $query->execute();
    $submission_data = $submission_q->fetchObject();
    $dest_path = $submission_data->directory_name . '/';
    foreach ($_FILES['files']['name'] as $file_form_name => $file_name)
    {
        if ($file_name)
        {
            /* checking file type */
            if (strstr($file_form_name, 'literature_report'))
            {
                $file_type = 'L';
            } //strstr($file_form_name, 'upload_circuit_simulation_developed_process')
            switch ($file_type)
            {
                case 'L':
                    if (file_exists($root_path . $dest_path . $_FILES['files']['name'][$file_form_name]))
                    {
                         drupal_set_message(t("Error uploading file. File !filename already exists.", array('!filename' => $_FILES['files']['name'][$file_form_name])), 'error');
                        //unlink($root_path . $dest_path . $_FILES['files']['name'][$file_form_name]);
                    } //file_exists($root_path . $dest_path . $_FILES['files']['name'][$file_form_name])
                    /* uploading file */
                    else if (move_uploaded_file($_FILES['files']['tmp_name'][$file_form_name], $root_path . $dest_path . $_FILES['files']['name'][$file_form_name]))
                    {
                        $query_ab_f = "SELECT * FROM mixed_signal_marathon_literature_survey WHERE id = :submission_id";
                        $args_ab_f = array(
                            ":submission_id" => $submission_id,
                        );
                        $query_ab_f_result = db_query($query_ab_f, $args_ab_f)->fetchObject();
                        unlink($root_path . $dest_path . $query_ab_f_result->report_file);
                        $query = "UPDATE mixed_signal_marathon_literature_survey set 
                         report_file = :report_file
                         WHERE id = :submission_id";
                            $args = array(
                                ":report_file" => $_FILES['files']['name'][$file_form_name],
                                ":submission_id" => $submission_id,
                            );
                        $updateresult = db_query($query, $args);
                        drupal_set_message($file_name . ' uploaded successfully.', 'status');
                    } //move_uploaded_file($_FILES['files']['tmp_name'][$file_form_name], $root_path . $dest_path . $_FILES['files']['name'][$file_form_name])
                    else
                    {
                        drupal_set_message('Error uploading file : ' . $dest_path . $file_name, 'error');
                    }
                    break;
            }

        }
    }
    drupal_set_message('Updated successfully', 'status'); 
    drupal_goto('mixed-signal-design-marathon/proposed');
}

function view_mscd_literature_report_submission_form($form, $form_state){
    global $user;
    $submission_id = arg(3);
    if ($user->uid == 0)
    {
        $msg = drupal_set_message(t('It is mandatory to log in on this website to edit your submission. If you are new user please create a new account first.'), 'error');
        //drupal_goto('esim-circuit-simulation-project');
        drupal_goto('user/login', array('query' => drupal_get_destination()));
        return $msg;
    } //$user->uid == 0
    $query = db_select('mixed_signal_marathon_literature_survey');
    $query->fields('mixed_signal_marathon_literature_survey');
    $query->condition('id', $submission_id);
    //$query->range(0, 1);
    $submission_q = $query->execute();
    $submission_data = $submission_q->fetchObject();
    $form = array();
    $form['participant_name'] = array(
        '#title' => t('Participant Name'),
        '#type' => 'item',
        '#markup' => $submission_data->participant_name
    );
    $form['participant_email'] = array(
        '#type' => 'item',
        '#title' => t('Email'),
        '#markup' => $submission_data->participant_email,
    );
    $form['institute'] = array(
        '#type' => 'item',
        '#title' => t('Name of the college/institute'),
        '#markup' => $submission_data->institute
    );
    $form['circuit_name'] = array(
        '#title' => t('Circuit Name'),
        '#type' => 'item',
        '#markup' => $submission_data->circuit_name
    );
    $form['circuit_type'] = array(
        '#type' => 'item',
        '#title' => t('Type of the circuit'),
        '#markup' => $submission_data->circuit_type
    );
    $form['reference_files']['literature_report'] = array(
        '#type' => 'item',
        '#markup' => l('Download Report', 'mixed-signal-design-marathon/download/literature-report/' . $submission_data->id)
    );

    $form["submit"] = array(
        "#type" => "submit",
    '#weight' => '6',
        "#value" => "Submit"
    );
    return $form;
}