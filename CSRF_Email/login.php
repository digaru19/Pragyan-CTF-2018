<?php

require "helpers.php";

$email = $_POST['email'];
$password = $_POST['password'];

if(isset($email) and isset($password)) {
    $req->email = $email;
    $req->password = $password;

    $json_req = json_encode($req);

    $result = post_data("http://localhost:8000/auth", $json_req);
    if($result === False) {
        die("500 Internal server error. Please contact the admins.");
    }

    $resp = json_decode($result);
    if($resp->is_valid === True) {
        session_start();
        $_SESSION['logged_in'] = True;
        $_SESSION['email'] = $email;
        $_SESSION['team_id'] = $resp->team_id;
        $_SESSION['team_name'] = $resp->team_name;
        echo $_SESSION['logged_in'];
        redirect("http://localhost/ss/C/admin_management.php");   
    }

}

?>

<!DOCTYPE html>
<html>
<head>
    <title>Pragyan CTF Admins</title>
<style type="text/css">
#creds {
    margin-left: auto;
    margin-right: auto;
    margin-top: 10%;   
    padding: 20px;
    width: 30%;
    border: 1px solid black;
}    
#creds input {
    align-self: center;
    align-content: center;
    margin: 5px;
}
</style>

</head>
<body>

<form id='creds' action='#' method="POST">
Email : <span style="width: 10px; height: 10px; " </span> <input type="text" name="email"> <br>
Password : <input type="password" name="password"> <br>
<input type="submit" value="Login"> 
</form>


</body>
</html>
