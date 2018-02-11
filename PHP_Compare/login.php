<?php

session_start();

require "helpers.php";

$email = $_POST['email'];
$password = $_POST['password'];

$req = [
    "email" => $email,
    "password" => $password
];

$response = post_data("http://localhost/ss/G/auth.php", $req);

if($response == true) {
    $_SESSION['logged_in'] = true;
    $_SESSION['p'] = $response;
    if($email === 'admin') {
        $_SESSION['is_admin'] = true;
    }
    redirect('http://localhost/ss/G/homepage.php');
}
else {
    die("Invalid Email-Password combination !!");
}

?>
