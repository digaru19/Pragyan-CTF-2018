<?php

session_start();

require "helpers.php";

if(! check_login())
    redirect($LOGIN_URL);

?>

<!DOCTYPE html>
<html>
<head>
    <title>Homepage</title>
</head>
<body>

<p style="float: right">
</p>
<p style="clear: both"></p>

<p style='height:30px; width:100%;'> </p>

<center>

<h2> Welcome !! </h2>
<br><br>

<?php
    if(isset($_SESSION['is_admin'])) {
        echo "Flag :- ".$flag;
    }
?>


</center>

</body>
</html>
