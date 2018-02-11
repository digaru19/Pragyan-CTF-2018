<?php

require "helpers.php";

$email = $_POST['email'];
$password = $_POST['password'];

if(!isset($email) || !isset($password))
    return;

// if(auth_service_active() === false) {
//     return;
// }

if(strlen($email) > 20 || strlen($password) > 32) {
        echo "Username/Password too big.";
        return;
    }

if(verify_email_password($email, $password) === true)  {
    echo "true";
    return;
}

// echo "vvvv";

?>
