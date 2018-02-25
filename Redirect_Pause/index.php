
<?php

require "helpers.php";
session_start();


if(isset($_POST['email']) && isset($_POST['password'])) {
    $email = $_POST['email'];
    $password = $_POST['password'];

    if(verify_email_password($email, $password) === true) {
        $_SESSION['logged_in'] = true;
        
        if(isset($_POST['is_admin'])) {
            if($_POST['is_admin'] === 'on') {
                redirect("/ss/R/admin.php");
            }
        }

        redirect("/ss/R/dashboard.php");
    }
    else {
        echo "Invalid user credentials !!";
        die();
    }
}

?>

<!DOCTYPE html>
<html>
<head>
    <title>Login</title>
    <style type="text/css">
#header {
    height: 20px;
    width: 100%;
}
#login_form{
    width: 40%;
    margin-left: auto;
    margin-right: auto;
    margin-top: 25px;
    border: 1px solid grey;  
    padding: 10px;
    line-height: 25px;
    background-color: #fdebd0 ;
}

#login_form input {
    margin-top: 20px;
}

</style>
</head>
<body style='background-color:  #fadbd8 ' >
<div id="header"> 
</div>

<div id="login_form" >
    <center>
    <form action="#" method="POST">
        <label>Email: </label>
        <input id='email' type="text" name="email" maxlength="200" placeholder="Enter Email">
        <br>
        <label>Password: </label>
        <input id='passwd' type="password" name="password" maxlength="200" placeholder="Enter Password">
        <br>
        <input id='admin_button' type="checkbox" name="is_admin" value="on"> <label for='admin_button'> I'm Admin. </label>
        <br>
        <input type="submit" value="Login">
    </form>
    </center>
</div>

</body>
</html>
