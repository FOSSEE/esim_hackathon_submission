<?php
function soc_marathon_download_literature_report()
{
    global $user;
    $submission_id = arg(3);
    $root_path = soc_marathon_hackathon_submission_files_path();
    //var_dump($root_path);die;
    $query = db_select('mixed_signal_soc_marathon_literature_survey');
    $query->fields('mixed_signal_soc_marathon_literature_survey');
    $query->condition('id', $submission_id);
    $submission_q = $query->execute();
    $submission_data = $submission_q->fetchObject();
    $directory_path = $submission_data->directory_name . '/';
    //var_dump($root_path . $directory_path . $submission_data->report_file);die;
    if($root_path . $directory_path . $submission_data->report_file){
          header('Content-Type: application/pdf');
            header('Content-disposition: attachment; filename=' . $submission_data->report_file );
            header('Content-Length: ' . filesize($root_path . $directory_path . $submission_data->report_file));
            ob_clean();
            readfile($root_path . $directory_path . $submission_data->report_file);
    }
    else{
            //unlink($zip_filename);
            drupal_set_message("File not found", 'error');
        drupal_goto('mixed-signal-design-marathon');
    }
    
}
function mscd_download_literature_report()
{
    global $user;
    $submission_id = arg(3);
    $root_path = mscd_hackathon_submission_files_path();
    //var_dump($root_path);die;
    $query = db_select('mixed_signal_marathon_literature_survey');
    $query->fields('mixed_signal_marathon_literature_survey');
    $query->condition('id', $submission_id);
    $submission_q = $query->execute();
    $submission_data = $submission_q->fetchObject();
    $directory_path = $submission_data->directory_name . '/';
    //var_dump($root_path . $directory_path . $submission_data->report_file);die;
    if($root_path . $directory_path . $submission_data->report_file){
          header('Content-Type: application/pdf');
            header('Content-disposition: attachment; filename=' . $submission_data->report_file );
            header('Content-Length: ' . filesize($root_path . $directory_path . $submission_data->report_file));
            ob_clean();
            readfile($root_path . $directory_path . $submission_data->report_file);
    }
    else{
            //unlink($zip_filename);
            drupal_set_message("File not found", 'error');
        drupal_goto('mixed-signal-design-marathon');
    }
    
}

function mscd_download_final_submission()
{
    global $user;
    $submission_id = arg(3);
    $root_path = mscd_hackathon_submission_files_path();
    //var_dump($submission_id);die;
    $query = db_select('mixed_signal_marathon_literature_survey');
    $query->fields('mixed_signal_marathon_literature_survey');
    $query->condition('id', $submission_id);
    $submission_q = $query->execute();
    $submission_data = $submission_q->fetchObject();
    $query = db_select('mixed_signal_marathon_final_submission_files');
    $query->fields('mixed_signal_marathon_final_submission_files');
    $query->condition('literature_survey_id', $submission_id);
    $final_submission_q = $query->execute();
    //$final_submission_data = $final_submission_q->fetchObject();
    //var_dump($final_submission_q->rowCount());die;
    $zip_filename = $root_path . $submission_data->circuit_name . '.zip';
    $zip = new ZipArchive();
    $zip->open($zip_filename, ZipArchive::CREATE);
    while ($final_submission_data = $final_submission_q->fetchObject()) {
       // $zip_filename = $root_path . $final_submission_data->id . '.zip';
    /*    $query = db_select('mixed_signal_marathon_literature_survey');
    $query->fields('mixed_signal_marathon_literature_survey');
    $query->condition('id', $final_submission_data->literature_survey_id);
    $submission_q = $query->execute();
    $submission_data = $submission_q->fetchObject();
    $directory_path = $submission_data->directory_name . '/';
    */
        $zip->addFile($root_path . $final_submission_data->filepath, $directory_path . str_replace(' ', '_', basename($final_submission_data->filename)));
    }

    $zip_file_count = $zip->numFiles;
    $zip->close();
    if ($zip_file_count > 0) {
            header('Content-Type: application/zip');
            header('Content-disposition: attachment; filename="' . str_replace(' ', '_', $submission_data->circuit_name) . '.zip"');
            header('Content-Length: ' . filesize($zip_filename));
            ob_clean();
            readfile($zip_filename);
            unlink($zip_filename);
    } //$zip_file_count > 0
    else {
        drupal_set_message("There are no files in this circuit to download", 'error');
        drupal_goto('mixed-signal-design-marathon');
    }
}

function mscd_download_emails(){
    global $user;
    /* get pending submissions to be approved */
    if ($user->uid == 0)
    {
        $msg = drupal_set_message(t('It is mandatory to login on this website to download the email IDs of the participants. If you are new user please create a new account first.'), 'error');
        //drupal_goto('/pssp');
        drupal_goto('user/login', array('query' => drupal_get_destination()));
        return $msg;
    }
    $root_path = mscd_hackathon_submission_files_path();
    $my_submission_rows = array();
    $query = db_select('mixed_signal_marathon_literature_survey');
    $query->fields('mixed_signal_marathon_literature_survey');
    //$query->condition('approval_status', 2);
    //$query->condition('uid',$user->uid);
    $all_submissions_q = $query->execute();
    $participants_email_id_file = $root_path . "participants-emails.csv";
    //var_dump($participants_email_id_file);die;
    $fp = fopen($participants_email_id_file, "w");
            /* making the first row */
            $item = array(
                "Email ID"
            );
            fputcsv($fp, $item);

            while($row = $all_submissions_q->fetchObject()) {
                $item = array(
                    $row->participant_email
                );
                fputcsv($fp, $item);
            }
            fclose($fp);
            if($participants_email_id_file){
        ob_clean();
            header("Pragma: public");
            header("Expires: 0");
            header("Cache-Control: must-revalidate, post-check=0, pre-check=0");
            header("Cache-Control: public");
            header("Content-Description: File Transfer");
            header('Content-Type: application/csv');
            header('Content-disposition: attachment; filename=email-ids.csv');
            header('Content-Length:' . filesize($participants_email_id_file));
            header("Content-Transfer-Encoding: binary");
            header('Expires: 0');
            header('Pragma: no-cache');
            readfile($participants_email_id_file);
            /*ob_end_flush();
            ob_clean();
            flush();*/
        }
}


function soc_marathon_download_emails(){
    global $user;
    /* get pending submissions to be approved */
    if ($user->uid == 0)
    {
        $msg = drupal_set_message(t('It is mandatory to login on this website to download the email IDs of the participants. If you are new user please create a new account first.'), 'error');
        //drupal_goto('/pssp');
        drupal_goto('user/login', array('query' => drupal_get_destination()));
        return $msg;
    }
    $root_path = soc_marathon_hackathon_submission_files_path();
    $my_submission_rows = array();
    $query = db_select('mixed_signal_soc_marathon_literature_survey');
    $query->fields('mixed_signal_soc_marathon_literature_survey');
    //$query->condition('approval_status', 2);
    //$query->condition('uid',$user->uid);
    $all_submissions_q = $query->execute();
    $participants_email_id_file = $root_path . "soc-participants-emails.csv";
    //var_dump($participants_email_id_file);die;
    $fp = fopen($participants_email_id_file, "w");
            /* making the first row */
            $item = array(
                "Email ID"
            );
            fputcsv($fp, $item);

            while($row = $all_submissions_q->fetchObject()) {
                $item = array(
                    $row->participant_email
                );
                fputcsv($fp, $item);
            }
            fclose($fp);
            if($participants_email_id_file){
        ob_clean();
            header("Pragma: public");
            header("Expires: 0");
            header("Cache-Control: must-revalidate, post-check=0, pre-check=0");
            header("Cache-Control: public");
            header("Content-Description: File Transfer");
            header('Content-Type: application/csv');
            header('Content-disposition: attachment; filename=email-ids.csv');
            header('Content-Length:' . filesize($participants_email_id_file));
            header("Content-Transfer-Encoding: binary");
            header('Expires: 0');
            header('Pragma: no-cache');
            readfile($participants_email_id_file);
            /*ob_end_flush();
            ob_clean();
            flush();*/
        }
}
function soc_marathon_download_final_submission()
{
    global $user;
    $submission_id = arg(3);
    $root_path = soc_marathon_hackathon_submission_files_path();
    //var_dump($submission_id);die;
    $query = db_select('mixed_signal_soc_marathon_literature_survey');
    $query->fields('mixed_signal_soc_marathon_literature_survey');
    $query->condition('id', $submission_id);
    $submission_q = $query->execute();
    $submission_data = $submission_q->fetchObject();
    $query = db_select('mixed_signal_soc_marathon_final_submission_files');
    $query->fields('mixed_signal_soc_marathon_final_submission_files');
    $query->condition('literature_survey_id', $submission_id);
    $final_submission_q = $query->execute();
    //$final_submission_data = $final_submission_q->fetchObject();
    //var_dump($final_submission_q->rowCount());die;
    $zip_filename = $root_path . $submission_data->circuit_name . '.zip';
    $zip = new ZipArchive();
    $zip->open($zip_filename, ZipArchive::CREATE);
    while ($final_submission_data = $final_submission_q->fetchObject()) {
       // $zip_filename = $root_path . $final_submission_data->id . '.zip';
    /*    $query = db_select('mixed_signal_soc_marathon_literature_survey');
    $query->fields('mixed_signal_soc_marathon_literature_survey');
    $query->condition('id', $final_submission_data->literature_survey_id);
    $submission_q = $query->execute();
    $submission_data = $submission_q->fetchObject();
    $directory_path = $submission_data->directory_name . '/';
    */
        $zip->addFile($root_path . $final_submission_data->filepath, $directory_path . str_replace(' ', '_', basename($final_submission_data->filename)));
    }

    $zip_file_count = $zip->numFiles;
    $zip->close();
    if ($zip_file_count > 0) {
            header('Content-Type: application/zip');
            header('Content-disposition: attachment; filename="' . str_replace(' ', '_', $submission_data->circuit_name) . '.zip"');
            header('Content-Length: ' . filesize($zip_filename));
            ob_clean();
            readfile($zip_filename);
            unlink($zip_filename);
    } //$zip_file_count > 0
    else {
        drupal_set_message("There are no files in this circuit to download", 'error');
        drupal_goto('mixed-signal-soc-design-marathon');
    }
}