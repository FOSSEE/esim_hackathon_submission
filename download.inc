<?php
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