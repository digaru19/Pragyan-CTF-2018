<?php

require "helpers.php";
session_start();

if(!check_login()) {
    redirect("/ss/R/");
}

?>

<!DOCTYPE html>
<html>
<head>
    <title>Dashboard</title>
</head>
<body>

<center>
<h4>
The user dashboard platform is under development. Please visit again later. 
<br>
Thank You
</h4>
</center>

</body>
</html>
