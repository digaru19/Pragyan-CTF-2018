<?php

require "helpers.php";
session_start();

if(! check_login())
    redirect($login_url);


?>


<!DOCTYPE html>
<html>
<head>
    <title>Admin Management Page</title>

<style type="text/css">
#header {
    height: 20px;
    width: 100%;
}

#left {
    display: inline-block;
    margin: 10px;
    height: 500px;
    width: 20%;
    border: 1px solid grey;
}

#right {
    display: inline-block;
    margin: 10px;
    height: 500px;
    width: 75%;
    border: 1px solid grey;
}
</style>

</head>
<body>

<div id="header"> 
</div>

<div id="container">
    <div id="left">
        <ul>
        <li>Hello</li>
        <li>World</li>
        </ul>  
    </div>

    <div id="right">
        <ul>
        <li>Toppo</li>
        <li>Jiren</li>
        </ul> 
    </div>

</div>

</body>
</html>
