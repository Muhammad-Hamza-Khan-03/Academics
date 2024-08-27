<?php

// Create connection
$conn = mysqli_connect('localhost','root', '', 'userdata');

// Check connection
if ($conn) {
echo "Connected successfully";
}
else
{
    echo" failed";
}
if(isset($_POST["submit"]))
{
    mysqli_select_db($conn,'userdata');
    $user=$_POST['user'];
    $email=$_POST['email'];
    $phone=$_POST['phone'];
    $comment=$_POST['comment'];
    $query="insert into userinfodata(user,email,phone,comment)
    values ('$user','$email','$phone','$comment')";
    
   $data=mysqli_query($conn, $query);
    header('location:index.php');
}
?>