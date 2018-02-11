<?php

ini_set('error_reporting', E_STRICT);

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

function verify_email_password($email, $password) {
    $req->email = $email;
    $req->password = $password;

    print_r($req);

    $json_req = json_encode($req);

    $result = post_data("http://localhost:8000/email_auth", $json_req);
    if($result === False) {
        die("500 Internal server error. Please contact the CTF admins.");
    }

    $resp = json_decode($result);
    if($resp->is_valid === True) {
        return true;
    }
    else {
        return false;
    }
}

