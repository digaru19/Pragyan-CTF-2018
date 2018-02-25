<?php

require "helpers.php";

session_start();

unset($_SESSION['logged_in']);
unset($_SESSION['id']);
unset($_SESSION['id_type']);

redirect($LOGIN_URL);

?>
