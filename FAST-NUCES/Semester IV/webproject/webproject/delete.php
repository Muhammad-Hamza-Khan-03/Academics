<?php
include'userinfo.php';
$id=$_GET['id'];
$query="DELETE FROM userinfodata  where ID='$id'";
$data=mysqli_query($conn, $query);

if ($data)
{
    ?>
    <script type="text/javascript">
        alert("Data deleted");
        window.open("http://localhost/webproject/view.php")
        </script>
        <?php
}
else
{
    ?>
    <script type="text/javascript">
        alert("Data not deleted");
        </script> 
    <?php
}
