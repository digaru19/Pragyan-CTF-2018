<?php

session_start();

require "helpers.php";

if(! check_login())
    redirect($login_url);

$session_id = session_id();
$mail_body = $_POST['mail_body'];
$team_name = $_SESSION['team_name'];
$email = $_SESSION['email'];
$team_id = $_SESSION['team_id'];

if(!isset($mail_body) || !isset($email) || !isset($team_id) || !isset($team_name))
    redirect($admin_page);

$data->session_id = $session_id;
$data->mail_body = $mail_body;
$data->team_name = $team_name;
$data->email = $email;
$data->team_id = $team_id;

$json_req = json_encode($data);
$resp = post_data($mail_evaluator, $json_req);

echo "Request sent..";

?>
