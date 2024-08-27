<?php
include'userinfo.php';?>
<a href="index.php">home</a>
<table border="1px" cellpadding="10px" cellspacing="0">
      <tr>
<th>username</th>
<th>Email</th>
<th>contact</th>
<th>comments</th>
<th colspan="2">Actions</th>
</tr>

<?php
$query="SELECT * FROM userinfodata";
$data=mysqli_query($conn, $query);
$result=mysqli_num_rows($data);
if($result) {
    while($row=mysqli_fetch_array($data))
{ ?>
    <tr> 
        <td> <?php echo $row['user']; ?> 
     </td> 
     <td> <?php echo $row['email']; ?> 
     </td>
     <td> <?php echo $row['phone']; ?> 
     </td>
     <td> <?php echo $row['comment']; ?> 
     </td>
     <td><a href="update.php?id=<?php echo $row['ID']; ?>">Edit</a></td>
     <td><a onclick="return confirm('Are you sure , you want to delete ?')"href="delete.php?id=<?php echo $row['ID']; ?>">Delete</a></td>
    
     
    </tr>
<?php 
}
}
else
{
echo "eroorS";
}
?>
</table>
