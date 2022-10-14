<?php

$espIp = "192.168.68.193";

$con = new mysqli("localhost","root","","irrigacao");

// Check connection
if ($con -> connect_errno) {
    echo "Failed to connect to MySQL: " . $con -> connect_error;
    exit();
}

?>