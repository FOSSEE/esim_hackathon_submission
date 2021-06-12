<?php
function download_literature_survey_report()
{
	$submission_id = arg(3);
	// drupal_set_message('This feature is currently unavailabe. We will resumes it shorty.','error');
	//drupal_goto('textbook_run/'. $submission_id);
	//exit;
	//_latex_copy_script_file();
	_latex_generate_files($submission_id);
	/*$full_book = arg(4);
	if ($full_book == "1")
		_latex_generate_files($submission_id, TRUE);
	else
		_latex_generate_files($submission_id, FALSE);*/
}
/*function download_literature_survey_report()
{
	$submission_id = arg(3);
	$root_path = hackathon_submission_files_path();
	$dir_path = $root_path . "latex/";
	$submission_q = db_query("SELECT * FROM {hackathon_literature_survey} WHERE id = :id", array(
        ':id' => $submission_id
    ));
    $submission_data = $submission_q->fetchObject();
	//var_dump($dir_path);die;
	if (filesize($dir_path . $submission_data->id . "_literature_survey_report.pdf") == TRUE)
		{
			ob_clean();
			header("Pragma: public");
			header("Expires: 0");
			header("Cache-Control: must-revalidate, post-check=0, pre-check=0");
			header("Cache-Control: public");
			header("Content-Description: File Transfer");
			header('Content-Type: application/pdf');
			header('Content-disposition: attachment; filename="' . $submission_data->id . "_literature_survey_report.pdf'");
			header('Content-Length: ' . filesize($dir_path . $submission_data->id . "_literature_survey_report.pdf"));
			header("Content-Transfer-Encoding: binary");
			header('Expires: 0');
			header('Pragma: no-cache');
			@readfile($dir_path . $submission_data->id . "_literature_survey_report.pdf");
			ob_end_flush();
			ob_clean();
			flush();
		} //filesize($dir_path . $pdf_filename) == TRUE
		else
		{
			_latex_generate_files($submission_data->id);
			ob_clean();
			header("Pragma: public");
			header("Expires: 0");
			header("Cache-Control: must-revalidate, post-check=0, pre-check=0");
			header("Cache-Control: public");
			header("Content-Description: File Transfer");
			header('Content-Type: application/pdf');
			header('Content-disposition: attachment; filename="' . $submission_data->id . "_literature_survey_report.pdf'");
			header('Content-Length: ' . filesize($dir_path . $submission_data->id . "_literature_survey_report.pdf"));
			header("Content-Transfer-Encoding: binary");
			header('Expires: 0');
			header('Pragma: no-cache');
			@readfile($dir_path . $submission_data->id . "_literature_survey_report.pdf");
			ob_end_flush();
			ob_clean();
			flush();

		}
}*/