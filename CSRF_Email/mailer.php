<?php

require "helpers.php";

session_start();
if(! check_login())
    redirect($login_url);


?>


<!DOCTYPE html>
<html>
<head>
    <title>Mail Admin Bot</title>

<style type="text/css">
#header {
    height: 20px;
    width: 100%;
}
#mail_form{
    width: 40%;
    margin-left: auto;
    margin-right: auto;
    margin-top: 25px;
    border: 1px solid grey;  
    padding: 10px;
    line-height: 25px;

}
#txtArea {
    margin-top: 10px;
}
#subject {
    width: 300px;
}

</style>

</head>
<body>

<div id="header"> 
</div>

<div id="mail_form" >
    <center>
    <form action="http://localhost/ss/C/mail_bot.php" method="POST">
        <label>Subject: </label>
        <input id='subject' type="text" name="subject" maxlength="10" placeholder="Enter subject of the mail">
        <br> <br>
        <label>Format : </label>
        <select name='format'>
            <option value='plain'>Plain Text</option>
            <option value='html' >HTML</option>
        </select> <br> <br>
        <textarea id="txtArea" rows="15" cols="60" name='mail_body' placeholder="Enter your mail body."></textarea>
        <br> <br>
        <input type="submit" value="Send mail to Admin bot">
    </form>
    </center>
</div>


</body>
</html>
