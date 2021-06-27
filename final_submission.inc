<?php
function add_final_submission_report_submission(){
    global $user;
    if ($user->uid == 0)
    {
        $msg = drupal_set_message(t('It is mandatory to log in on this website to upload your submission. If you are new user please create a new account first.'), 'error');
        //drupal_goto('esim-circuit-simulation-project');
        drupal_goto('user/login', array('query' => drupal_get_destination()));
        return $msg;
    } //$user->uid == 0
    $query = db_select('hackathon_literature_survey');
    $query->fields('hackathon_literature_survey');
    $query->condition('uid', $user->uid);
    //$query->condition('id', $submission_id);
    //$query->range(0, 1);
    $submission_q = $query->execute();
    $literature_submission_data = $submission_q->fetchObject();
    if($literature_submission_data){
    $today = date("Y-m-d H:i:s");
    //var_dump($today);die;
    $start_date = "2021-06-27 23:59:59.0"; 
    $last_date = "2021-06-30 23:59:59.0";
    $return_html = '';
    if($today < $start_date){
        $return_html .= '<p>You can submit your Final report at anytime between 28-06-2021, 12 AM and 30-06-2021, 23:59 PM.</p>';
    }
    elseif($today > $last_date){
        $return_html .= '<p>Final Report Submissions are closed.</p>';
    }
    else{
        $submission_form = drupal_get_form("add_final_submission_report_submission_form");
        $return_html .= drupal_render($submission_form);
    }
    return $return_html;
    }
    else{
        drupal_set_message('We regret to inform that we have not received your literature survey report', 'error');
        drupal_goto('');
    }
}
function add_project_files_submission(){
    global $user;
    if ($user->uid == 0)
    {
        $msg = drupal_set_message(t('It is mandatory to log in on this website to upload your project files. If you are new user please create a new account first.'), 'error');
        //drupal_goto('esim-circuit-simulation-project');
        drupal_goto('user/login', array('query' => drupal_get_destination()));
        return $msg;
    } //$user->uid == 0
    $query = db_select('hackathon_literature_survey');
    $query->fields('hackathon_literature_survey');
    $query->condition('uid', $user->uid);
    //$query->condition('id', $submission_id);
    //$query->range(0, 1);
    $submission_q = $query->execute();
    $literature_submission_data = $submission_q->fetchObject();
    if($literature_submission_data){
    $today = date("Y-m-d H:i:s");
    //var_dump($today);die;
    $start_date = "2021-06-27 23:59:59.0"; 
    $last_date = "2021-06-30 23:59:59.0";
    $return_html = '';
    if($today < $start_date){
        $return_html .= '<p>You can upload your project files anytime between 28-06-2021, 12 AM and 30-06-2021, 23:59 PM.</p>';
    }
    elseif($today > $last_date){
        $return_html .= '<p>Submissions are closed.</p>';
    }
    else{
        $submission_form = drupal_get_form("hackathon_submission_add_project_files_form");
        $return_html .= drupal_render($submission_form);
    }
    return $return_html;
    }
    else{
        drupal_set_message('We regret to inform that we have not received your literature survey report', 'error');
        drupal_goto('');
    }
}

function add_final_submission_report_submission_form($form, $form_state, $no_js_use = FALSE)
{
    global $user;
    $query = db_select('hackathon_literature_survey');
    $query->fields('hackathon_literature_survey');
    $query->condition('uid', $user->uid);
    $query->orderBy('id', 'DESC');
    $query->range(0, 1);
    $proposal_q = $query->execute();
    $literature_survey_data = $proposal_q->fetchObject();
    $query = db_select('hackathon_final_submission');
    $query->fields('hackathon_final_submission');
    $query->condition('uid', $user->uid);
    $query->orderBy('id', 'DESC');
    $query->range(0, 1);
    $proposal_q = $query->execute();
    $final_submission_data = $proposal_q->fetchObject();
    if ($final_submission_data)
    {
         drupal_set_message(t('We have already received your submission. Use the edit submission below to make changes to your submission'), 'status');
        drupal_goto('hackathon-submission/proposed');
            return;
         //$proposal_data->approval_status == 0 || $proposal_data->approval_status == 1
    }//$proposal_data
    $form = array();
    $form['participant_name'] = array(
    	'#title' => t('Participant Name'),
    	'#type' => 'textfield',
    	'#size' => 70,
    	'#maxlength' => 70,
        '#required' => TRUE,
        '#default_value' => $literature_survey_data->participant_name,
        '#disabled' => TRUE
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
        '#default_value' => $literature_survey_data->institute,
        '#disabled' => TRUE
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
        '#default_value' => $literature_survey_data->circuit_name,
        '#disabled' => TRUE
    );
    $form['abstract'] = array(
        '#title' => t('Abstract'),
        '#type' => 'textarea',
        '#description' => t('The abstract should contain minimum 600 characters and not exceed more than 725 characters.<p><span style="color:red">Note: </span>Only alphanumeric values are allowed in the text. Do not add symbols in your text, you may not be able to generate the PDF of the report.</p>'),
        '#rows' => 5,
        '#minlength' => 600,
        '#maxlength' => 725,
        '#required' => TRUE,
        '#expandable' => TRUE
        /*'#ajax' => array(
        'callback' => 'update_length_ajax_callback',
        'wrapper' => 'length-div',
        'method' => 'replace',
        'effect' => 'fade',
        ),*/
    );
    /*$form['abstract_length'] = array(
        '#type' => 'textfield',
        '#default_value' => 0,
        '#value' => isset($form_state['values']['abstract']) ? strlen(trim(preg_replace('/\s+/',' ', $form_state['values']['abstract']))) : 0,
        '#prefix' => '<div id="length-div">',
        '#suffix' => '</div>',
        '#attributes' => array('readonly' => 'readonly'),
    );*/
    $form['circuit_details'] = array(
        '#title' => t('Circuit Details'),
        '#type' => 'textarea',
        '#description' => t('The circuit details should contain minimum 1334 characters and not exceed more than 1600 characters.<p><span style="color:red">Note: </span>Only alphanumeric values are allowed in the text. Do not add symbols in your text, you may not be able to generate the PDF of the report.</p>'),
        '#rows' => 5,
        '#minlength' => 1334,
        '#maxlength' => 1600,
        '#required' => TRUE,
        '#expandable' => TRUE
    );    
	$form['reference_files'] = array(
        '#type' => 'fieldset',
        '#title' => t('Upload Files'),
        '#collapsible' => FALSE,
        '#collapsed' => FALSE
    );
    $form['reference_files']['reference_circuit'] = array(
        '#type' => 'file',
        '#title' => t('Upload circuit diagram snapshot from esim'),
        '#size' => 48,
        '#upload_validators' => array(
                'file_validate_extensions' => array(variable_get('reference_circuit_extensions', '')),
                // Pass the maximum file size in bytes
                /*'file_validate_size' => array(5*1024*1024),*/
              ),
        '#description' => t('Upload image(900x600 pixels) with allowed extensions only. No spaces or any special characters allowed in filename.') . '<br />' . t('<span style="color:red;">Allowed file extensions: ') . variable_get('reference_circuit_extensions', '') . '</span>'
    );
    $form['reference_files']['reference_waveform'] = array(
        '#type' => 'file',
        '#title' => t('Upload waveform from SPICE simulations'),
        '#size' => 48,
        '#upload_validators' => array(
                'file_validate_extensions' => array(variable_get('reference_circuit_extensions', '')),
                // Pass the maximum file size in bytes
                /*'file_validate_size' => array(5*1024*1024),*/
              ),
        '#description' => t('Upload image(900x600 pixels) with allowed extensions only. No spaces or any special characters allowed in filename.') . '<br />' . t('<span style="color:red;">Allowed file extensions: ') . variable_get('reference_waveform_extensions', '') . '</span>'
    );

    $form['final_bib_reference_fieldset'] = array(
            '#type' => 'fieldset',
            '#title' => t('References'),
            '#tree' => TRUE,
            '#prefix' => '<div id="final_bib_reference-fieldset-wrapper">',
            '#suffix' => '</div>'
        );         
            if (empty($form_state['num_final_bib_reference'])) {
                $form_state['num_final_bib_reference'] = 1;
            }
            $temp = 0;
            for ($i = 0; $i < $form_state['num_final_bib_reference']; $i++) {
                $temp = $i;
                $form['final_bib_reference_fieldset'][$i]["s_text"] = array(
                    "#type" => "item",
                    "#markup" => "<h4><label>Reference: " . ($temp + 1) . "</label></h4>"
                );
                $form['final_bib_reference_fieldset'][$i]["resource_link"] = array(
                    "#type" => "textfield",
                    "#title" => "Link to the resource",
                    "#default_value" => "",
                    '#required' => TRUE,
                    '#maxlength' => 180,
                    '#description' => t('Maximum character limit is 180 characters')
                );
                $form['final_bib_reference_fieldset'][$i]["resource_title"] = array(
                    "#type" => "textfield",
                    "#title" => "Resource Paper title",
                    "#default_value" => "",
                    '#required' => TRUE,
                    '#maxlength' => 180,
                    '#description' => t('Maximum character limit is 180 characters')
                );
                $form['final_bib_reference_fieldset'][$i]["resource_author"] = array(
                    "#type" => "textfield",
                    "#title" => "Author of the resource",
                    "#default_value" => "",
                    '#required' => TRUE,
                    '#maxlength' => 180,
                    '#description' => t('Maximum character limit is 180 characters')
                );
               
            }
            $form["final_bib_reference_count"] = array(
                "#type" => "hidden",
                "#value" => $temp
            );
            if($i <3){
            $form['final_bib_reference_fieldset']['add_final_bib_reference'] = array(
                '#type' => 'submit',
                '#value' => t('Add more'),
                '#limit_validation_errors' => array(),
                '#submit' => array(
                    'final_bib_reference_add_more_add_one'
                ),
                '#ajax' => array(
                    'callback' => 'final_bib_reference_add_more_callback',
                    'wrapper' => 'final_bib_reference-fieldset-wrapper'
                )
            );
        }
            if ($form_state['num_final_bib_reference'] > 1) {
                $form['final_bib_reference_fieldset']['remove_final_bib_reference'] = array(
                    '#type' => 'submit',
                    '#value' => t('Remove'),
                    '#limit_validation_errors' => array(),
                    '#submit' => array(
                        'final_bib_reference_add_more_remove_one'
                    ),
                    '#ajax' => array(
                        'callback' => 'final_bib_reference_add_more_callback',
                        'wrapper' => 'final_bib_reference-fieldset-wrapper'
                    )
                );
            }
            if ($no_js_use) {
                if (!empty($form['final_bib_reference_fieldset']['remove_final_bib_reference']['#ajax'])) {
                    unset($form['final_bib_reference_fieldset']['remove_final_bib_reference']['#ajax']);
                }
                unset($form['final_bib_reference_fieldset']['add_final_bib_reference']['#ajax']);
            }

    $form["submit"] = array(
        "#type" => "submit",
	'#weight' => '6',
        "#value" => "Submit"
    );
    return $form;
}
/*function update_length_ajax_callback($form, &$form_state)
{
    return $form['abstract_length'];
}*/

  function final_bib_reference_add_more_callback($form, $form_state) {
    return $form['final_bib_reference_fieldset'];
}


function final_bib_reference_add_more_add_one($form, &$form_state) {

 if (!isset($form_state['num_final_bib_reference'])) {
        $form_state['num_final_bib_reference'] = 0;
        $form_state['num_final_bib_reference']++;
    }

    $form_state['num_final_bib_reference']++;
    $form_state['rebuild'] = TRUE;
}

function final_bib_reference_add_more_remove_one($form, &$form_state) {
    if ($form_state['num_final_bib_reference'] > 1) {
        $form_state['num_final_bib_reference']--;
    }
    $form_state['rebuild'] = TRUE;
}


function add_final_submission_report_submission_form_validate($form, &$form_state){
    //$validate_special_chars = array("_", "&", "%", "#", "{", "}", "^", "µ","̊", "±", "ω", "π", "Σ", "Ω", "ρ", "λ", "φ","α","β", "∆", "∑", ":");
    if (strlen($form_state['values']['abstract']) < 600)
        {
            form_set_error('abstract', t('Minimum charater limit is 600 charaters, but abstract is currently ' . strlen($form_state['values']['abstract']) . ' characters'));
        }
    if (strlen($form_state['values']['circuit_details']) < 1334)
        {
            form_set_error('circuit_details', t('Minimum charater limit is 1334 charaters, but circuit details is currently ' . strlen($form_state['values']['circuit_details']) . ' characters'));
        }
        //var_dump($form_state['values']['abstract']);die;
        //var_dump(preg_match_all('/[\^%&()#.:_+]/',$form_state['values']['abstract'], $out) ? $out[0] : 'no match');die;
    if(!hs_check_special_characters($form_state['values']['abstract']))
    {
        form_set_error('abstract', t('Only alphanumeric values are allowed. Please remove other characters in your abstract'));
    }
    if(!hs_check_special_characters($form_state['values']['circuit_details']))
    {
        form_set_error('circuit_details', t('Only alphanumeric values are allowed. Please remove other characters in your circuit details'));
    }
    if (isset($_FILES['files']))
    {
        /* check if atleast one source or result file is uploaded */
        if (!($_FILES['files']['name']['reference_circuit']))
            form_set_error('reference_circuit', t('Please upload the circuit diagram'));
        if(!($_FILES['files']['name']['reference_waveform']))
            form_set_error('reference_waveform', t('Please upload the waveform'));
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

function add_final_submission_report_submission_form_submit($form, &$form_state){
    global $user;
    $query = db_select('hackathon_literature_survey');
    $query->fields('hackathon_literature_survey');
    $query->condition('uid', $user->uid);
    $query->orderBy('id', 'DESC');
    $query->range(0, 1);
    $proposal_q = $query->execute();
    $literature_survey_data = $proposal_q->fetchObject();
    $directory_name = $literature_survey_data->directory_name;
    $literature_survey_id =  $literature_survey_data->id;
    $root_path = hackathon_submission_files_path();
    $v = $form_state["values"];
    $result = "INSERT INTO hackathon_final_submission 
    (
    uid, 
    literature_survey_id,
    abstract, 
    circuit_details,
    creation_date
    ) VALUES
    (
    :uid, 
    :literature_survey_id, 
    :abstract, 
    :circuit_details,
    :creation_date
    )";
    $args = array(
        ":uid" => $user->uid,
        ":literature_survey_id" => $literature_survey_id,
        ":abstract" => trim($v['abstract']),
        ":circuit_details" => trim($v['circuit_details']),
        ":creation_date" => time()
        );
    //  var_dump($args);die;
    //var_dump($result);die;
    $final_submission_id = db_query($result, $args, array(
        'return' => Database::RETURN_INSERT_ID
    ));
    //Adding references to db

    $final_bib_reference_upload = 0;
            for ($i = 0; $i <= $v["final_bib_reference_count"]; $i++) {
                //$f_id=$v['final_bib_reference_fieldset'][$i]["f_id"];
                if ($v['final_bib_reference_fieldset'][$i]["resource_link"] != "") {
                    $final_bib_referencequery = "INSERT INTO hackathon_final_submission_bib_references (final_submission_id,resource_link,resource_title,resource_author) VALUES (:final_submission_id,:resource_link,:resource_title,:resource_author)";
                    $final_bib_referenceargs = array(
                        ":final_submission_id" => $final_submission_id,
                        ":resource_link" => trim($v['final_bib_reference_fieldset'][$i]["resource_link"]),
                        ":resource_title" => trim($v['final_bib_reference_fieldset'][$i]["resource_title"]),
                        ":resource_author" => trim($v['final_bib_reference_fieldset'][$i]["resource_author"])
                    );
                    /* storing the row id in $result */
                    $final_bib_referenceresult = db_query($final_bib_referencequery, $final_bib_referenceargs, array(
                        'return' => Database::RETURN_INSERT_ID
                    ));
                    if ($final_bib_referenceresult != 0) {
                        $final_bib_referenceupload++;
                    }
                }
            }


    $proposal_dir_path = $directory_name . '/';
    $dest_path1 = $proposal_dir_path . 'final_submission_files/';
    $dest_path = $dest_path1 . 'reference_files/';
    //var_dump($dest_path1);die;    
    if (!is_dir($root_path . $proposal_dir_path))
            //mkdir($root_path . $proposal_dir_path);
        drupal_set_message('Folder does not exist', 'error');
    //var_dump($root_path . $proposal_dir_path);die;
    if (!is_dir($root_path . $dest_path1))
            mkdir($root_path . $dest_path1);
    if (!is_dir($root_path . $dest_path))
            mkdir($root_path . $dest_path);
    //var_dump($root_path . $dest_path);die;
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
                        $query = "INSERT INTO {hackathon_final_submission_files} (final_submission_id, uid, filename, filepath, filemime, filesize, filetype, file_creation_date)
          VALUES (:final_submission_id, :uid, :filename, :filepath, :filemime, :filesize, :filetype, :file_creation_date)";
                            $args = array(
                                ":final_submission_id" => $final_submission_id,
                                ":uid" => $user->uid,
                                ":filename" => $_FILES['files']['name'][$file_form_name],
                                ":filepath" => $dest_path . $_FILES['files']['name'][$file_form_name],
                                ":filemime" => mime_content_type($root_path . $dest_path . $_FILES['files']['name'][$file_form_name]),
                                ":filesize" => $_FILES['files']['size'][$file_form_name],
                                ":filetype" => $file_type,
                                ":file_creation_date" => time()
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
                        $query = "INSERT INTO {hackathon_final_submission_files} (final_submission_id, uid, filename, filepath, filemime, filesize, filetype, file_creation_date)
          VALUES (:final_submission_id, :uid, :filename, :filepath, :filemime, :filesize, :filetype, :file_creation_date)";
                            $args = array(
                                ":final_submission_id" => $final_submission_id,
                                ":uid" => $user->uid,
                                ":filename" => $_FILES['files']['name'][$file_form_name],
                                ":filepath" => $dest_path . $_FILES['files']['name'][$file_form_name],
                                ":filemime" => mime_content_type($root_path . $dest_path . $_FILES['files']['name'][$file_form_name]),
                                ":filesize" => $_FILES['files']['size'][$file_form_name],
                                ":filetype" => $file_type,
                                ":file_creation_date" => time()
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
        if (!$final_submission_id)
        {
            drupal_set_message(t('Error receiving your submission. Please try again.'), 'error');
            return;
        }
        drupal_set_message(t('Your submission is successful'), 'status');
    drupal_goto('hackathon-submission/proposed');
}


function edit_final_submission_form($form, $form_state, $no_js_use = FALSE){
    global $user;
    $final_submission_id = arg(3);
    if ($user->uid == 0)
    {
        $msg = drupal_set_message(t('It is mandatory to log in on this website to edit your submission. If you are new user please create a new account first.'), 'error');
        //drupal_goto('esim-circuit-simulation-project');
        drupal_goto('user/login', array('query' => drupal_get_destination()));
        return $msg;
    } //$user->uid == 0
    $query = db_select('hackathon_final_submission');
    $query->fields('hackathon_final_submission');
    //$query->condition('uid', $user->uid);
    $query->condition('id', $final_submission_id);
    //$query->range(0, 1);
    $final_submission_q = $query->execute();
    $final_submission_data = $final_submission_q->fetchObject();

    $query = db_select('hackathon_literature_survey');
    $query->fields('hackathon_literature_survey');
    $query->condition('uid', $user->uid);
    $query->condition('id', $final_submission_data->literature_survey_id);
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
        '#default_value' => $submission_data->circuit_name,
        '#disabled' => TRUE
    );
    $form['abstract'] = array(
        '#title' => t('Abstract'),
        '#type' => 'textarea',
        '#description' => t('The abstract should contain minimum 600 characters and not exceed more than 725 characters.<p><span style="color:red">Note: </span>Only alphanumeric values are allowed in the text.  Do not add symbols in your text, you may not be able to generate the PDF of the report.</p>'),
        '#rows' => 5,
        '#minlength' => 600,
        '#maxlength' => 725,
        '#required' => TRUE,
        '#default_value' => $final_submission_data->abstract
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
        '#description' => t('The circuit details should contain minimum 1334 characters and not exceed more than 1600 characters.<p><span style="color:red">Note:  </span>Only alphanumeric values are allowed in the text.  Do not add symbols in your text, you may not be able to generate the PDF of the report.</p>'),
        '#rows' => 5,
        '#minlength' => 1334,
        '#maxlength' => 1600,
        '#required' => TRUE,
        '#default_value' => $final_submission_data->circuit_details
    );    
    $form['reference_files'] = array(
        '#type' => 'fieldset',
        '#title' => t('Upload Reference Files'),
        '#collapsible' => FALSE,
        '#collapsed' => FALSE
    );
    //var_dump($final_submission_id);die;
    $existing_uploaded_C_file = default_value_for_uploaded_final_files("C", $final_submission_id);
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
    $existing_uploaded_W_file = default_value_for_uploaded_final_files("W", $final_submission_id);
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
    $query_bib_ref = db_select('hackathon_final_submission_bib_references');
    $query_bib_ref->fields('hackathon_final_submission_bib_references');
    $query_bib_ref->condition('final_submission_id', $final_submission_id);
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
                    "#default_value" => $row_s->resource_link,
                    '#maxlength' => 180,
                    '#description' => t('Maximum character limit is 180 characters')
                );
                $form['existing_bib_reference_fieldset'][$i]["resource_title"] = array(
                    "#type" => "textfield",
                    "#title" => "Resource Title",
                    "#default_value" => $row_s->resource_title,
                    '#maxlength' => 180,
                    '#description' => t('Maximum character limit is 180 characters')
                );
                $form['existing_bib_reference_fieldset'][$i]["resource_author"] = array(
                    "#type" => "textfield",
                    "#title" => "Resource Author",
                    "#default_value" => $row_s->resource_author,
                    '#maxlength' => 180,
                    '#description' => t('Maximum character limit is 180 characters')
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
                    '#maxlength' => 180,
                    '#description' => t('Maximum character limit is 180 characters')
                );
                $form['bib_reference_fieldset'][$i]["resource_title"] = array(
                    "#type" => "textfield",
                    "#title" => "Resource Paper title",
                    "#default_value" => "",
                    '#maxlength' => 180,
                    '#description' => t('Maximum character limit is 180 characters')
                );
                $form['bib_reference_fieldset'][$i]["resource_author"] = array(
                    "#type" => "textfield",
                    "#title" => "Author of the resource",
                    "#default_value" => "",
                    '#maxlength' => 180,
                    '#description' => t('Maximum character limit is 180 characters')
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



function edit_final_submission_form_validate($form, &$form_state){
    //$validate_special_chars = array("_", "&", "%", "#", "{", "}", "^", "µ","̊", "±", "ω", "π", "Σ", "Ω", "ρ", "λ", "φ","α","β", "∆", "∑", ":", "(", ")", "+", "/", "-", ",", ".", "'");
    if (strlen($form_state['values']['abstract']) < 600)
        {
            form_set_error('abstract', t('Minimum charater limit for abstract is 600 charaters'));
        }
    if (strlen($form_state['values']['circuit_details']) < 1334)
        {
            form_set_error('circuit_details', t('Minimum charater limit for circuit details is 1334 charaters'));
        }
    if(!hs_check_special_characters($form_state['values']['abstract']))
    {
        form_set_error('abstract', t('Only alphanumeric values are allowed. Please remove other characters in your abstract'));
    }
    if(!hs_check_special_characters($form_state['values']['circuit_details']))
    {
        form_set_error('circuit_details', t('Only alphanumeric values are allowed. Please remove other characters in your circuit details'));
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



function edit_final_submission_form_submit($form, $form_state){
    $final_submission_id = arg(3);
    global $user;
    $v = $form_state['values'];
    $root_path = hackathon_submission_files_path();
    $query = "UPDATE hackathon_final_submission SET 
                abstract=:abstract,
                circuit_details=:circuit_details
                WHERE id=:submission_id";
    $args = array(
        ':abstract' => $v['abstract'],
        ':circuit_details' => $v['circuit_details'],
        ':submission_id' => $final_submission_id
    );
    $result = db_query($query, $args);
    /*$final_submission_id = db_query($query, $args, array(
        'return' => Database::RETURN_INSERT_ID
    ));*/
    $query = db_select('hackathon_final_submission');
    $query->fields('hackathon_final_submission');
    //$query->condition('uid', $user->uid);
    $query->condition('id', $final_submission_id);
    $query->range(0, 1);
    $proposal_q = $query->execute();
    $final_submission_data = $proposal_q->fetchObject();
    $query = db_select('hackathon_literature_survey');
    $query->fields('hackathon_literature_survey');
    $query->condition('uid', $user->uid);
    $query->condition('id', $final_submission_data->literature_survey_id);
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
                    $bib_referencequery = "INSERT INTO hackathon_final_submission_bib_references (final_submission_id,resource_link,resource_title,resource_author) VALUES (:final_submission_id,:resource_link,:resource_title,:resource_author)";
                    $bib_referenceargs = array(
                        ":final_submission_id" => $final_submission_id,
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
                    $bib_referencequery = "UPDATE hackathon_final_submission_bib_references set
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
                        $query_ab_f = "SELECT * FROM hackathon_final_submission_files WHERE final_submission_id = :final_final_submission_id AND filetype = 
                :filetype";
                        $args_ab_f = array(
                            ":final_submission_id" => $final_submission_id,
                            ":filetype" => $file_type
                        );
                        $query_ab_f_result = db_query($query_ab_f, $args_ab_f)->fetchObject();
                        unlink($root_path . $dest_path . $query_ab_f_result->filename);
                        $query = "UPDATE {hackathon_final_submission_files} set 
                         filename = :filename, 
                         filepath = :filepath,
                         filemime = :filemime,
                         filesize = :filesize
                         WHERE final_submission_id = :final_submission_id and filetype = :filetype";
                            $args = array(
                                ":filename" => $_FILES['files']['name'][$file_form_name],
                                ":filepath" => $dest_path . $_FILES['files']['name'][$file_form_name],
                                ":filemime" => mime_content_type($root_path . $dest_path . $_FILES['files']['name'][$file_form_name]),
                                ":filesize" => $_FILES['files']['size'][$file_form_name],
                                ":final_submission_id" => $final_submission_id,
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
                        $query_ab_f = "SELECT * FROM hackathon_final_submission_files WHERE final_submission_id = :final_submission_id AND filetype = 
                :filetype";
                        $args_ab_f = array(
                            ":final_submission_id" => $final_submission_id,
                            ":filetype" => $file_type
                        );
                        $query_ab_f_result = db_query($query_ab_f, $args_ab_f)->fetchObject();
                        unlink($root_path . $dest_path . $query_ab_f_result->filename);
                        $query = "UPDATE {hackathon_final_submission_files} set 
                         filename = :filename, 
                         filepath = :filepath,
                         filemime = :filemime,
                         filesize = :filesize
                         WHERE final_submission_id = :final_submission_id and filetype = :filetype";
                            $args = array(
                                ":filename" => $_FILES['files']['name'][$file_form_name],
                                ":filepath" => $dest_path . $_FILES['files']['name'][$file_form_name],
                                ":filemime" => mime_content_type($root_path . $dest_path . $_FILES['files']['name'][$file_form_name]),
                                ":filesize" => $_FILES['files']['size'][$file_form_name],
                                ":final_submission_id" => $final_submission_id,
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

function default_value_for_uploaded_final_files($filetype, $final_submission_id)
{
    $filetype = $filetype;
    $final_submission_id = $final_submission_id;
    $query = db_select('hackathon_final_submission_files');
    $query->fields('hackathon_final_submission_files');
    $query->condition('final_submission_id', $final_submission_id);
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


function hackathon_submission_add_project_files_form($form, $form_state, $no_js_use = FALSE)
{
    global $user;
    if ($user->uid == 0)
    {
        $msg = drupal_set_message(t('It is mandatory to log in on this website to upload your submission. If you are new user please create a new account first.'), 'error');
        //drupal_goto('esim-circuit-simulation-project');
        drupal_goto('user');
        return $msg;
    } //$user->uid == 0
    $query = db_select('hackathon_literature_survey');
    $query->fields('hackathon_literature_survey');
    $query->condition('uid', $user->uid);
    $query->orderBy('id', 'DESC');
    $query->range(0, 1);
    $proposal_q = $query->execute();
    $literature_survey_data = $proposal_q->fetchObject();

    $query = db_select('hackathon_final_submission_project_files');
    $query->fields('hackathon_final_submission_project_files');
    $query->condition('uid', $user->uid);
    $query->orderBy('id', 'DESC');
    //$query->range(0, 1);
    $proposal_q = $query->execute();
    $project_files_data = $proposal_q->fetchObject();
    if ($project_files_data)
    {
            drupal_set_message(t('We have already received your project files. Use the edit project files option below to modify/update your project files'), 'status');
            drupal_goto('hackathon-submission/proposed');
            return;
    } //$proposal_data
    $form = array();
    $form['participant_name'] = array(
        '#title' => t('Name'),
        '#type' => 'textfield',
        '#disabled' => TRUE,
        '#default_value' => $literature_survey_data->participant_name
    );
    $form['circuit_name'] = array(
        '#title' => t('Circuit Name'),
        '#type' => 'textfield',
        '#default_value' => $literature_survey_data->circuit_name,
        '#disabled' => TRUE,
        '#size' => 70,
        '#maxlength' => 70,
        '#required' => TRUE
    );
    $form['source_file'] = array(
        '#type' => 'fieldset',
        '#title' => t('Upload Main Netlist file<span style="color:red">*</span>'),
        '#collapsible' => FALSE,
        '#collapsed' => FALSE
    );
    $form['source_file']['main_netlist'] = array(
        '#type' => 'file',
        //'#title' => t('Upload circuit diagram'),
        '#size' => 48,
        '#description' => t('Upload filenames with allowed extensions only. No spaces or any special characters allowed in filename.') . '<br />' . t('<span style="color:red;">Allowed file extensions: ') . variable_get('main_netlist_file_extensions', '') . '</span>'
    );
    $form['final_project_files'] = array(
        '#type' => 'fieldset',
        '#tree' => TRUE,
        '#title' => t('Upload Subcircuit files'),
    );
    $form['final_project_files']['subcircuit_files'] = array(
        '#type' => 'file',
        //'#title' => t('Upload circuit diagram'),
        '#size' => 48,
        '#description' => t('Upload filenames with allowed extensions only. No spaces or any special characters allowed in filename.') . '<br />' . t('<span style="color:red;">Allowed file extensions: ') . variable_get('subcircuit_file_extensions', '') . '</span>'
    );
    $form['project_files'] = array(
        '#type' => 'fieldset',
        '#title' => t('Upload Readme file<span style="color:red">*</span>'),
        '#collapsible' => FALSE,
        '#collapsed' => FALSE
    );
    $form['project_files']['readme'] = array(
        '#type' => 'file',
        //'#title' => t('Upload circuit diagram'),
        '#size' => 48,
        '#description' => t('Upload filenames with allowed extensions only. No spaces or any special characters allowed in filename.') . '<br />' . t('<span style="color:red;">Allowed file extensions: ') . variable_get('readme_file_extensions', '') . '</span>'
    );
    $form["submit"] = array(
        "#type" => "submit",
    '#weight' => '6',
        "#value" => "Submit"
    );
    return $form;
}


function hackathon_submission_add_project_files_form_validate($form, &$form_state){
    if (isset($_FILES['files']))
    {
        /* check if atleast one source or result file is uploaded */
        if (!($_FILES['files']['name']['main_netlist']))
            form_set_error('main_netlist', t('Main netlist file is mandatory'));
        if(!($_FILES['files']['name']['readme']))
            form_set_error('readme', t('Readme  file is mandatory'));
        /* check for valid filename extensions */
        foreach ($_FILES['files']['name'] as $file_form_name => $file_name)
        {
            if ($file_name)
            {
                /* checking file type */
                if (strstr($file_form_name, 'main_netlist')){
                    $file_type = 'N';
                    $fnames = substr($_FILES['files']['name'][$file_form_name], strpos($_FILES['files']['name'][$file_form_name], ".") + 1);
                    $temp_extension = $fnames;
                }
                else if (strstr($file_form_name, 'readme')){
                    $file_type = 'R';
                    $fnames = explode('.', strtolower($_FILES['files']['name'][$file_form_name]));
                    $temp_extension = end($fnames);
                }
                else{
                    $file_type = 'S';
                    $fnames = explode('.', strtolower($_FILES['files']['name'][$file_form_name]));
                    $temp_extension = end($fnames);
                }
                $allowed_extensions_str = '';
                switch ($file_type)
                {
                    case 'N':
                        $allowed_extensions_str = variable_get('main_netlist_file_extensions', '');
                        break;
                    case 'S':
                        $allowed_extensions_str = variable_get('subcircuit_file_extensions', '');
                        break;
                    case 'R':
                        $allowed_extensions_str = variable_get('readme_file_extensions', '');
                        break;
                }
                $allowed_extensions = explode(',', $allowed_extensions_str);
                //$fnames = substr($_FILES['files']['name'][$file_form_name], strpos($_FILES['files']['name'][$file_form_name], ".") + 1);
                //$temp_extension = end($fnames);
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

function hackathon_submission_add_project_files_form_submit($form, &$form_state){
    global $user;
    $query = db_select('hackathon_literature_survey');
    $query->fields('hackathon_literature_survey');
    $query->condition('uid', $user->uid);
    $query->orderBy('id', 'DESC');
    $query->range(0, 1);
    $proposal_q = $query->execute();
    $literature_survey_data = $proposal_q->fetchObject();
    $literature_survey_id = $literature_survey_data->id;
    $root_path = hackathon_submission_files_path();
    $directory_name = $literature_survey_data->directory_name;
    $dest_path = $directory_name . '/project_files/';
    if (!is_dir($root_path . $dest_path))
            mkdir($root_path . $dest_path);
    //var_dump($root_path . $dest_path);die;
        foreach ($_FILES['files']['name'] as $file_form_name => $file_name)
        {
        if ($file_name)
        {
            // checking file type 
            //$file_type = 'S';
            if (strstr($file_form_name, 'main_netlist'))
            {
                $file_type = 'N';
            } //strstr($file_form_name, 'upload_circuit_simulation_developed_process')
            else if (strstr($file_form_name, 'readme'))
            {
                $file_type = 'R';
            }
            else
            {
                $file_type = 'S';
            } 
            switch ($file_type)
            {
                case 'N':
                    if (file_exists($root_path . $dest_path . $_FILES['files']['name'][$file_form_name]))
                    {
                         drupal_set_message(t("Error uploading file. File !filename already exists.", array('!filename' => $_FILES['files']['name'][$file_form_name])), 'error');
                        //unlink($root_path . $dest_path . $_FILES['files']['name'][$file_form_name]);
                    } //file_exists($root_path . $dest_path . $_FILES['files']['name'][$file_form_name])
                    // uploading file 
                    if (move_uploaded_file($_FILES['files']['tmp_name'][$file_form_name], $root_path . $dest_path . $_FILES['files']['name'][$file_form_name]))
                    {
                        $query = "INSERT INTO hackathon_final_submission_project_files(literature_submission_id, uid, filename, filepath, filemime, filesize, filetype, file_creation_date) VALUES
                          (:literature_submission_id, :uid, :filename, :filepath, :filemime, :filesize, :filetype, :file_creation_date)";
                            $args = array(
                                ":literature_submission_id" => $literature_survey_id,
                                ":uid" => $user->uid,
                                ":filename" => $file_name,
                                ":filepath" => $dest_path . $file_name,
                                ":filemime" => mime_content_type($root_path . $dest_path . $_FILES['files']['name'][$file_form_name]),
                                ":filesize" => filesize($root_path . $dest_path . $_FILES['files']['name'][$file_form_name]),
                                ":filetype" => $file_type,
                                ":file_creation_date" => time()
                            );
                        
                        $updateresult = db_query($query, $args);
                        //var_dump($args);die;

                        drupal_set_message($file_name . ' uploaded successfully.', 'status');
                    } //move_uploaded_file($_FILES['files']['tmp_name'][$file_form_name], $root_path . $dest_path . $_FILES['files']['name'][$file_form_name])
                    else
                    {
                        drupal_set_message('Error uploading file : ' . $dest_path . '/' . $file_name, 'error');
                    }
                    break;
                case 'R':
                    if (file_exists($root_path . $dest_path . $_FILES['files']['name'][$file_form_name]))
                    {
                         drupal_set_message(t("Error uploading file. File !filename already exists.", array('!filename' => $_FILES['files']['name'][$file_form_name])), 'error');
                        //unlink($root_path . $dest_path . $_FILES['files']['name'][$file_form_name]);
                    } //file_exists($root_path . $dest_path . $_FILES['files']['name'][$file_form_name])
                    // uploading file 
                    if (move_uploaded_file($_FILES['files']['tmp_name'][$file_form_name], $root_path . $dest_path . $_FILES['files']['name'][$file_form_name]))
                    {
                        $query = "INSERT INTO hackathon_final_submission_project_files(literature_submission_id, uid, filename, filepath, filemime, filesize, filetype, file_creation_date) VALUES
                          (:literature_submission_id, :uid, :filename, :filepath, :filemime, :filesize, :filetype, :file_creation_date)";
                            $args = array(
                                ":literature_submission_id" => $literature_survey_id,
                                ":uid" => $user->uid,
                                ":filename" => $file_name,
                                ":filepath" => $dest_path . $file_name,
                                ":filemime" => mime_content_type($root_path . $dest_path . $_FILES['files']['name'][$file_form_name]),
                                ":filesize" => filesize($root_path . $dest_path . $_FILES['files']['name'][$file_form_name]),
                                ":filetype" => $file_type,
                                ":file_creation_date" => time()
                            );
                        
                        $updateresult = db_query($query, $args);
                        //var_dump($args);die;

                        drupal_set_message($file_name . ' uploaded successfully.', 'status');
                    } //move_uploaded_file($_FILES['files']['tmp_name'][$file_form_name], $root_path . $dest_path . $_FILES['files']['name'][$file_form_name])
                    else
                    {
                        drupal_set_message('Error uploading file : ' . $dest_path . '/' . $file_name, 'error');
                    }
                    break;
                case 'S':
                    if (file_exists($root_path . $dest_path . $_FILES['files']['name'][$file_form_name]))
                    {
                         drupal_set_message(t("Error uploading file. File !filename already exists.", array('!filename' => $_FILES['files']['name'][$file_form_name])), 'error');
                        //unlink($root_path . $dest_path . $_FILES['files']['name'][$file_form_name]);
                    } //file_exists($root_path . $dest_path . $_FILES['files']['name'][$file_form_name])
                    // uploading file 
                    if (move_uploaded_file($_FILES['files']['tmp_name'][$file_form_name], $root_path . $dest_path . $_FILES['files']['name'][$file_form_name]))
                    {
                        $query = "INSERT INTO hackathon_final_submission_project_files(literature_submission_id, uid, filename, filepath, filemime, filesize, filetype, file_creation_date) VALUES
                          (:literature_submission_id, :uid, :filename, :filepath, :filemime, :filesize, :filetype, :file_creation_date)";
                            $args = array(
                                ":literature_submission_id" => $literature_survey_id,
                                ":uid" => $user->uid,
                                ":filename" => $file_name,
                                ":filepath" => $dest_path . $file_name,
                                ":filemime" => mime_content_type($root_path . $dest_path . $_FILES['files']['name'][$file_form_name]),
                                ":filesize" => filesize($root_path . $dest_path . $_FILES['files']['name'][$file_form_name]),
                                ":filetype" => $file_type,
                                ":file_creation_date" => time()
                            );
                        
                        $updateresult = db_query($query, $args);
                        //var_dump($args);die;

                        drupal_set_message($file_name . ' uploaded successfully.', 'status');
                    } //move_uploaded_file($_FILES['files']['tmp_name'][$file_form_name], $root_path . $dest_path . $_FILES['files']['name'][$file_form_name])
                    else
                    {
                        drupal_set_message('Error uploading file : ' . $dest_path . '/' . $file_name, 'error');
                    }
                    break;
                }
        } //$file_name
    }
    drupal_set_message(t('Your submission is successful'), 'status');
    drupal_goto('hackathon-submission/proposed');
}

function edit_project_files_form($form, $form_state, $no_js_use = FALSE){
    global $user;
    $literature_survey_id = arg(3);
    if ($user->uid == 0)
    {
        $msg = drupal_set_message(t('It is mandatory to log in on this website to edit your submission. If you are new user please create a new account first.'), 'error');
        //drupal_goto('esim-circuit-simulation-project');
        drupal_goto('user/login', array('query' => drupal_get_destination()));
        return $msg;
    }
    $query = db_select('hackathon_literature_survey');
    $query->fields('hackathon_literature_survey');
    $query->condition('uid', $user->uid);
    $query->condition('id', $literature_survey_id);
    //$query->range(0, 1);
    $literature_submission_q = $query->execute();
    $literature_submission_data = $literature_submission_q->fetchObject();
    $query = db_select('hackathon_final_submission_project_files');
    $query->fields('hackathon_final_submission_project_files');
    $query->condition('literature_submission_id', $literature_survey_id);
    $project_files_data = $query->execute()->fetchObject();
    if(!$project_files_data){
        drupal_set_message('We have not yet received your project files');
        drupal_goto('hackathon-submission/add/project-files');
    }

    $form = array();
    $form['participant_name'] = array(
        '#title' => t('Participant Name'),
        '#type' => 'textfield',
        '#disabled' => TRUE,
        '#size' => 70,
        '#maxlength' => 70,
        '#default_value' => $literature_submission_data->participant_name
    );
    $form['circuit_name'] = array(
        '#title' => t('Circuit Name'),
        '#type' => 'textfield',
        '#size' => 70,
        '#maxlength' => 70,
        '#disabled' => TRUE,
        '#default_value' => $literature_submission_data->circuit_name
    );
    $form['edit_source_file'] = array(
        '#type' => 'fieldset',
        '#title' => t('Edit Main Netlist file'),
        '#collapsible' => FALSE,
        '#collapsed' => FALSE
    );
$existing_uploaded_N_file = default_value_for_uploaded_project_files("N", $literature_survey_id);
    if (!$existing_uploaded_N_file)
    {
        $existing_uploaded_N_file = new stdClass();
        $existing_uploaded_N_file->filename = "No file uploaded";
    }
    $form['edit_source_file']['main_netlist'] = array(
        '#type' => 'file',
        //'#title' => t('Upload circuit diagram'),
        '#size' => 48,
        '#description' => t('Upload filenames with allowed extensions only. No spaces or any special characters allowed in filename.') . '<br />' . t('<span style="color:red;">Current File :</span> ') . $existing_uploaded_N_file->filename . '<br />' . t('<span style="color:red;">Allowed file extensions: ') . variable_get('main_netlist_file_extensions', '') . '</span>'
    );
    $form['edit_final_project_files'] = array(
        '#type' => 'fieldset',
        '#title' => t('Edit Subcircuit File'),
        '#collapsible' => FALSE,
        '#collapsed' => FALSE
    );
    $existing_uploaded_S_file = default_value_for_uploaded_project_files("S", $literature_survey_id);
    if (!$existing_uploaded_S_file)
    {
        $existing_uploaded_S_file = new stdClass();
        $existing_uploaded_S_file->filename = "No file uploaded";
    }
    $form['edit_final_project_files']['subcircuit_files'] = array(
        '#type' => 'file',
        //'#title' => t('Edit Subcircuit file'),
        '#size' => 48,
        '#description' => t('Upload filenames with allowed extensions only. No spaces or any special characters allowed in filename.') . '<br />' . t('<span style="color:red;">Current File :</span> ') . $existing_uploaded_S_file->filename . '<br />' . t('<span style="color:red;">Allowed file extensions: ') . variable_get('subcircuit_file_extensions', '') . '</span>'
    );
    $form['edit_project_files'] = array(
        '#type' => 'fieldset',
        '#title' => t('Edit Readme file'),
        '#collapsible' => FALSE,
        '#collapsed' => FALSE
    );
$existing_uploaded_R_file = default_value_for_uploaded_project_files("R", $literature_survey_id);
    if (!$existing_uploaded_R_file)
    {
        $existing_uploaded_R_file = new stdClass();
        $existing_uploaded_R_file->filename = "No file uploaded";
    }
    $form['edit_project_files']['readme'] = array(
        '#type' => 'file',
        //'#title' => t('Upload circuit diagram'),
        '#size' => 48,
        '#description' => t('Upload filenames with allowed extensions only. No spaces or any special characters allowed in filename.') . '<br />' . t('<span style="color:red;">Current File :</span> ') . $existing_uploaded_R_file->filename . '<br />' . t('<span style="color:red;">Allowed file extensions: ') . variable_get('readme_file_extensions', '') . '</span>'
    );
    $form["submit"] = array(
        "#type" => "submit",
        "#value" => "Submit"
    );
    return $form;
}

function edit_project_files_form_validate($form, $form_state){
    if (isset($_FILES['files']))
    {
        /* check for valid filename extensions */
        foreach ($_FILES['files']['name'] as $file_form_name => $file_name)
        {
            if ($file_name)
            {
                /* checking file type */
                if (strstr($file_form_name, 'main_netlist')){
                    $file_type = 'N';
                    $fnames = substr($_FILES['files']['name'][$file_form_name], strpos($_FILES['files']['name'][$file_form_name], ".") + 1);
                    $temp_extension = $fnames;
                }
                else if (strstr($file_form_name, 'readme')){
                    $file_type = 'R';
                    $fnames = explode('.', strtolower($_FILES['files']['name'][$file_form_name]));
                    $temp_extension = end($fnames);
                }
                else if (strstr($file_form_name, 'subcircuit_files')){
                    $file_type = 'S';
                    $fnames = explode('.', strtolower($_FILES['files']['name'][$file_form_name]));
                    $temp_extension = end($fnames);
                }
                $allowed_extensions_str = '';
                switch ($file_type)
                {
                    case 'N':
                        $allowed_extensions_str = variable_get('main_netlist_file_extensions', '');
                        break;
                    case 'S':
                        $allowed_extensions_str = variable_get('subcircuit_file_extensions', '');
                        break;
                    case 'R':
                        $allowed_extensions_str = variable_get('readme_file_extensions', '');
                        break;
                }
                $allowed_extensions = explode(',', $allowed_extensions_str);
                //$fnames = substr($_FILES['files']['name'][$file_form_name], strpos($_FILES['files']['name'][$file_form_name], ".") + 1);
                //$temp_extension = end($fnames);
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

function edit_project_files_form_submit($form, $form_state){
    global $user;
    $v = $form_state['values'];
    $root_path = hackathon_submission_files_path();
    $literature_survey_id = arg(3);
    $query = db_select('hackathon_literature_survey');
    $query->fields('hackathon_literature_survey');
    $query->condition('uid', $user->uid);
    $query->condition('id', $literature_survey_id);
    //$query->range(0, 1);
    $literature_submission_q = $query->execute();
    $literature_submission_data = $literature_submission_q->fetchObject();
    //$proposal_dir_path = $literature_submission_data->directory_name . '/project_files/';
    //$dest_path1 = $proposal_dir_path . 'literature_survey/';
    $dest_path = $literature_submission_data->directory_name . '/project_files/';
    foreach ($_FILES['files']['name'] as $file_form_name => $file_name)
    {
        if ($file_name)
        {
            /* checking file type */
            if (strstr($file_form_name, 'main_netlist'))
            {
                $file_type = 'N';
            } //strstr($file_form_name, 'upload_circuit_simulation_developed_process')
            else if (strstr($file_form_name, 'readme'))
            {
                $file_type = 'R';
            }
            else if (strstr($file_form_name, 'subcircuit_files'))
            {
                $file_type = 'S';
            } 
            switch ($file_type)
            {
                case 'N':
                    if (file_exists($root_path . $dest_path . $_FILES['files']['name'][$file_form_name]))
                    {
                         drupal_set_message(t("Error uploading file. File !filename already exists.", array('!filename' => $_FILES['files']['name'][$file_form_name])), 'error');
                        //unlink($root_path . $dest_path . $_FILES['files']['name'][$file_form_name]);
                    } //file_exists($root_path . $dest_path . $_FILES['files']['name'][$file_form_name])
                    /* uploading file */
                    else if (move_uploaded_file($_FILES['files']['tmp_name'][$file_form_name], $root_path . $dest_path . $_FILES['files']['name'][$file_form_name]))
                    {
                        $query_ab_f = "SELECT * FROM hackathon_final_submission_project_files WHERE literature_submission_id = :literature_submission_id  AND filetype = 
                :filetype";
                        $args_ab_f = array(
                            ":literature_submission_id" => $literature_survey_id,
                            ":filetype" => $file_type
                        );
                        $query_ab_f_result = db_query($query_ab_f, $args_ab_f)->fetchObject();
                        unlink($root_path . $dest_path . $query_ab_f_result->filename);
                        $query = "UPDATE {hackathon_final_submission_project_files} set 
                         filename = :filename, 
                         filepath = :filepath,
                         filemime = :filemime,
                         filesize = :filesize
                         WHERE literature_submission_id = :literature_submission_id and filetype = :filetype";
                            $args = array(
                                ":filename" => $_FILES['files']['name'][$file_form_name],
                                ":filepath" => $dest_path . $_FILES['files']['name'][$file_form_name],
                                ":filemime" => mime_content_type($root_path . $dest_path . $_FILES['files']['name'][$file_form_name]),
                                ":filesize" => $_FILES['files']['size'][$file_form_name],
                                ":literature_submission_id" => $literature_survey_id,
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
                case 'R':
                    if (file_exists($root_path . $dest_path . $_FILES['files']['name'][$file_form_name]))
                    {
                         drupal_set_message(t("Error uploading file. File !filename already exists.", array('!filename' => $_FILES['files']['name'][$file_form_name])), 'error');
                        //unlink($root_path . $dest_path . $_FILES['files']['name'][$file_form_name]);
                    } //file_exists($root_path . $dest_path . $_FILES['files']['name'][$file_form_name])
                    /* uploading file */
                    else if (move_uploaded_file($_FILES['files']['tmp_name'][$file_form_name], $root_path . $dest_path . $_FILES['files']['name'][$file_form_name]))
                    {
                        $query_ab_f = "SELECT * FROM hackathon_final_submission_project_files WHERE literature_submission_id = :literature_submission_id AND filetype = 
                :filetype";
                        $args_ab_f = array(
                            ":literature_submission_id" => $literature_survey_id,
                            ":filetype" => $file_type
                        );
                        $query_ab_f_result = db_query($query_ab_f, $args_ab_f)->fetchObject();
                        unlink($root_path . $dest_path . $query_ab_f_result->filename);
                        $query = "UPDATE {hackathon_final_submission_project_files} set 
                         filename = :filename, 
                         filepath = :filepath,
                         filemime = :filemime,
                         filesize = :filesize
                         WHERE literature_submission_id = :literature_submission_id and filetype = :filetype";
                            $args = array(
                                ":filename" => $_FILES['files']['name'][$file_form_name],
                                ":filepath" => $dest_path . $_FILES['files']['name'][$file_form_name],
                                ":filemime" => mime_content_type($root_path . $dest_path . $_FILES['files']['name'][$file_form_name]),
                                ":filesize" => $_FILES['files']['size'][$file_form_name],
                                ":literature_submission_id" => $literature_survey_id,
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
                case 'S':
                    if (file_exists($root_path . $dest_path . $_FILES['files']['name'][$file_form_name]))
                    {
                         drupal_set_message(t("Error uploading file. File !filename already exists.", array('!filename' => $_FILES['files']['name'][$file_form_name])), 'error');
                        //unlink($root_path . $dest_path . $_FILES['files']['name'][$file_form_name]);
                    } //file_exists($root_path . $dest_path . $_FILES['files']['name'][$file_form_name])
                    /* uploading file */
                    else if (move_uploaded_file($_FILES['files']['tmp_name'][$file_form_name], $root_path . $dest_path . $_FILES['files']['name'][$file_form_name]))
                    {
                        $query_ab_f = "SELECT * FROM hackathon_final_submission_project_files WHERE literature_submission_id = :literature_submission_id  AND filetype = 
                :filetype";
                        $args_ab_f = array(
                            ":literature_submission_id" => $literature_survey_id,
                            ":filetype" => $file_type
                        );
                        $query_ab_f_result = db_query($query_ab_f, $args_ab_f)->fetchObject();
                        unlink($root_path . $dest_path . $query_ab_f_result->filename);
                        $query = "UPDATE {hackathon_final_submission_project_files} set 
                         filename = :filename, 
                         filepath = :filepath,
                         filemime = :filemime,
                         filesize = :filesize
                         WHERE literature_submission_id = :literature_submission_id and filetype = :filetype";
                            $args = array(
                                ":filename" => $_FILES['files']['name'][$file_form_name],
                                ":filepath" => $dest_path . $_FILES['files']['name'][$file_form_name],
                                ":filemime" => mime_content_type($root_path . $dest_path . $_FILES['files']['name'][$file_form_name]),
                                ":filesize" => $_FILES['files']['size'][$file_form_name],
                                ":literature_submission_id" => $literature_survey_id,
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
    drupal_goto('hackathon-submission/proposed');
}

function default_value_for_uploaded_project_files($filetype, $submission_id)
{
    $filetype = $filetype;
    $literature_survey_id = $submission_id;
    $query = db_select('hackathon_final_submission_project_files');
    $query->fields('hackathon_final_submission_project_files');
    $query->condition('literature_submission_id', $submission_id);
    $selected_files_array = "";
    if ($filetype == "N")
    {
        $query->condition('filetype', $filetype);
        $filetype_q = $query->execute()->fetchObject();
        return $filetype_q;
        //var_dump($filetype_q);die;
    } //$filetype == "A"
    elseif ($filetype == "R")
    {
        $query->condition('filetype', $filetype);
        $filetype_q = $query->execute()->fetchObject();
        return $filetype_q;
    }
    elseif ($filetype == "S")
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