<?php

require "helpers.php";

session_start();

if(!check_login()) {
    redirect("/ss/R/");
}
else {
    header('Location: /ss/R/unavailable.php');
}

?>

<!DOCTYPE html>
<html>
<head>
    <title>Admin Dashboard</title>
</head>
<body>

<center>
<h4>
Redirect
<br><br>
The Admin panel is under construction. Redirecting ...
</h4>
<br><br>
Flag :- pctf{y0u=Sh0Uldn'1/h4v3*s33n,1his.:)}
</center>

</body>
</html>
