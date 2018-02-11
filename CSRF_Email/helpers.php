<?php

ini_set('error_reporting', E_STRICT);

$login_url = 'http://localhost/ss/C/login.php';
$admin_page = 'http://localhost/ss/C/admin_management.php';
$mail_evaluator = 'http://localhost:9000/evaluate';

function post_data($url, $data) {
    $ch = curl_init();

    curl_setopt($ch, CURLOPT_URL,            $url );
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1 );
    curl_setopt($ch, CURLOPT_POST,           True );
    curl_setopt($ch, CURLOPT_POSTFIELDS,     $data ); 
    curl_setopt($ch, CURLOPT_HTTPHEADER,     array('Content-Type: application/json')); 

    $result = curl_exec($ch);

    curl_close($ch);
    return $result;
}

function redirect($url) {
    ob_start();
    header('Location: '.$url);
    ob_end_flush();
    die();
}

function check_login() {
    if (empty($_SESSION['logged_in'])) {
        return False;
    }
    if($_SESSION['logged_in'] === True)
        return True;
    return False;
}

?>
