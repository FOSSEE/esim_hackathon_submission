<?php
function add_literature_report_submission(){
    global $user;
    if ($user->uid == 0)
    {
        $msg = drupal_set_message(t('It is mandatory to log in on this website to upload your submission. If you are new user please create a new account first.'), 'error');
        //drupal_goto('esim-circuit-simulation-project');
        drupal_goto('user/login', array('query' => drupal_get_destination()));
        return $msg;
    } //$user->uid == 0
    $today = date("Y-m-d H:i:s");
    //var_dump($today);die;
    $start_date = "2021-06-17 23:59:59.0"; 
    $last_date = "2021-06-21 23:59:59.0";
    $return_html = '';
    if($today < $start_date){
        $return_html .= '<p>You can submit your Literature Survey report at anytime between 18-06-2021, 12 AM and 21-06-2021, 23:59 PM.</p>';
    }
    elseif($today > $last_date){
        $return_html .= '<p>Literature Survey Submissions are closed.</p>';
    }
    else{
        $submission_form = drupal_get_form("add_literature_report_submission_form");
        $return_html .= drupal_render($submission_form);
    }
    return $return_html;
}

function add_literature_report_submission_form($form, $form_state, $no_js_use = FALSE)
{
    
    $query = db_select('hackathon_literature_survey');
    $query->fields('hackathon_literature_survey');
    $query->condition('uid', $user->uid);
    $query->orderBy('id', 'DESC');
    $query->range(0, 1);
    $proposal_q = $query->execute();
    $proposal_data = $proposal_q->fetchObject();
    if ($proposal_data)
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
        '#required' => TRUE
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
        '#required' => TRUE
    );
    $form['abstract'] = array(
        '#title' => t('Abstract'),
        '#type' => 'textarea',
        '#description' => t('The abstract should not exceed more than 120 words'),
        '#rows' => 5,
        '#minlength' => 600,
        '#maxlength' => 725,
        '#required' => TRUE,
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
        '#description' => t('The circuit details should not exceed more than 250 words'),
        '#rows' => 5,
        '#minlength' => 1334,
        '#maxlength' => 1600,
        '#required' => TRUE
    );    
	$form['reference_files'] = array(
        '#type' => 'fieldset',
        '#title' => t('Upload Reference Files'),
        '#collapsible' => FALSE,
        '#collapsed' => FALSE
    );
    $form['reference_files']['reference_circuit'] = array(
        '#type' => 'file',
        '#title' => t('Upload reference circuit'),
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
        '#title' => t('Upload reference waveform'),
        '#size' => 48,
        '#upload_validators' => array(
                'file_validate_extensions' => array(variable_get('reference_circuit_extensions', '')),
                // Pass the maximum file size in bytes
                /*'file_validate_size' => array(5*1024*1024),*/
              ),
        '#description' => t('Upload image(900x600 pixels) with allowed extensions only. No spaces or any special characters allowed in filename.') . '<br />' . t('<span style="color:red;">Allowed file extensions: ') . variable_get('reference_waveform_extensions', '') . '</span>'
    );

    $form['bib_reference_fieldset'] = array(
            '#type' => 'fieldset',
            '#title' => t('References'),
            '#tree' => TRUE,
            '#prefix' => '<div id="bib_reference-fieldset-wrapper">',
            '#suffix' => '</div>'
        );         
            if (empty($form_state['num_bib_reference'])) {
                $form_state['num_bib_reference'] = 1;
            }
            $temp = 0;
            for ($i = 0; $i < $form_state['num_bib_reference']; $i++) {
                $temp = $i;
                $form['bib_reference_fieldset'][$i]["s_text"] = array(
                    "#type" => "item",
                    "#markup" => "<h4><label>Reference: " . ($temp + 1) . "</label></h4>"
                );
                $form['bib_reference_fieldset'][$i]["resource_link"] = array(
                    "#type" => "textfield",
                    "#title" => "Link to the resource",
                    "#default_value" => "",
                    '#required' => TRUE
                );
                $form['bib_reference_fieldset'][$i]["resource_title"] = array(
                    "#type" => "textfield",
                    "#title" => "Resource Paper title",
                    "#default_value" => "",
                    '#required' => TRUE
                );
                $form['bib_reference_fieldset'][$i]["resource_author"] = array(
                    "#type" => "textfield",
                    "#title" => "Author of the resource",
                    "#default_value" => "",
                    '#required' => TRUE
                );
               
            }
            $form["bib_reference_count"] = array(
                "#type" => "hidden",
                "#value" => $temp
            );
            if($i <3){
            $form['bib_reference_fieldset']['add_bib_reference'] = array(
                '#type' => 'submit',
                '#value' => t('Add more'),
                '#limit_validation_errors' => array(),
                '#submit' => array(
                    'bib_reference_add_more_add_one'
                ),
                '#ajax' => array(
                    'callback' => 'bib_reference_add_more_callback',
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
                        'bib_reference_add_more_remove_one'
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

  function bib_reference_add_more_callback($form, $form_state) {
    return $form['bib_reference_fieldset'];
}


function bib_reference_add_more_add_one($form, &$form_state) {

 if (!isset($form_state['num_bib_reference'])) {
        $form_state['num_bib_reference'] = 0;
        $form_state['num_bib_reference']++;
    }

    $form_state['num_bib_reference']++;
    $form_state['rebuild'] = TRUE;
}

function bib_reference_add_more_remove_one($form, &$form_state) {
    if ($form_state['num_bib_reference'] > 1) {
        $form_state['num_bib_reference']--;
    }
    $form_state['rebuild'] = TRUE;
}


function add_literature_report_submission_form_validate($form, &$form_state){
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

function add_literature_report_submission_form_submit($form, &$form_state){
    global $user;
    $root_path = hackathon_submission_files_path();
    $v = $form_state["values"];
    $circuit_name = trim($v['circuit_name']);
    $participant_name = trim($v['participant_name']);
    $directory_name = _hs_dir_name($circuit_name, $participant_name);
    $result = "INSERT INTO hackathon_literature_survey 
    (
    uid, 
    participant_name,
    participant_email,
    institute,
    circuit_name, 
    abstract, 
    circuit_details, 
    directory_name,
    creation_date
    ) VALUES
    (
    :uid, 
    :participant_name, 
    :participant_email,
    :institute, 
    :circuit_name, 
    :abstract, 
    :circuit_details,
    :directory_name,
    :creation_date
    )";
    $args = array(
        ":uid" => $user->uid,
        ":participant_name" => $participant_name,
        ":participant_email" => $v['participant_email'],
        ":institute" => trim($v['institute']),
        ":circuit_name" => $circuit_name,
        ":abstract" => trim($v['abstract']),
        ":circuit_details" => trim($v['circuit_details']),
        ":directory_name" => $directory_name,
        ":creation_date" => time()
        );
    //  var_dump($args);die;
    //var_dump($result);die;
    $submission_id = db_query($result, $args, array(
        'return' => Database::RETURN_INSERT_ID
    ));
    //Adding references to db

    $bib_reference_upload = 0;
            for ($i = 0; $i <= $v["bib_reference_count"]; $i++) {
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
                        $bib_referenceupload++;
                    }
                }
            }


    $proposal_dir_path = $directory_name . '/';
    $dest_path1 = $proposal_dir_path . 'literature_survey/';
    $dest_path = $dest_path1 . 'reference_files/';
    //var_dump($dest_path1);die;    
    if (!is_dir($root_path . $proposal_dir_path))
            mkdir($root_path . $proposal_dir_path);
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
                        $query = "INSERT INTO {hackathon_literature_survey_files} (submission_id, uid, filename, filepath, filemime, filesize, filetype, file_creation_date)
          VALUES (:submission_id, :uid, :filename, :filepath, :filemime, :filesize, :filetype, :file_creation_date)";
                            $args = array(
                                ":submission_id" => $submission_id,
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
                        $query = "INSERT INTO {hackathon_literature_survey_files} (submission_id, uid, filename, filepath, filemime, filesize, filetype, file_creation_date)
          VALUES (:submission_id, :uid, :filename, :filepath, :filemime, :filesize, :filetype, :file_creation_date)";
                            $args = array(
                                ":submission_id" => $submission_id,
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
    //_latex_generate_files($submission_id);
        if (!$submission_id)
        {
            drupal_set_message(t('Error receiving your submission. Please try again.'), 'error');
            return;
        }
        drupal_set_message(t('Your submission is successful'), 'status');
    drupal_goto('hackathon-submission/proposed');
}