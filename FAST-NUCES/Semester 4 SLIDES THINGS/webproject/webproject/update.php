<?php
include'userinfo.php';
$id=$_GET['id'];
$select="SELECT * FROM userinfodata  where ID='$id'";
$data=mysqli_query($conn, $select);
$row=mysqli_fetch_array($data);

?>
<div>
        <form action="" method="post">
          <div class="form-group">
            <label>username</label>
            <input type="text" name="user" autocomplete="off" value=" <?php echo $row['user']?>" class="form-control" >
          </div>
          <div class="form-group">
            <label>Email</label>
            <input value=" <?php echo $row['email']?> "type="text" name="email" autocomplete="off" class="form-control">
          </div>
          <div class="form-group">
            <label>phone</label>
            <input value=" <?php echo $row['phone']?>"type="text" name="phone" autocomplete="off" class="form-control">

            <div class="form-group">
              <label>comment</label>
            <input value=" <?php echo $row['comment']?>"type="text" name="comment">
              
              <div>
                <input type="submit" class="btn btn-secondary" name="update" value="update ">
              </div>
              
              <div><a href="view.php" type="submit"class="btn btn-primary">Back</a></div>
        </form>
      </div>
 <?php 
      if(isset($_POST["update"]))
{
    mysqli_select_db($conn,'userdata');
    $user=$_POST['user'];
    $email=$_POST['email'];
    $phone=$_POST['phone'];
    $comment=$_POST['comment'];
    $update="UPDATE userinfodata set user=' $user', email='$email',phone='$phone',comment='$comment' WHERE id='$id'";
    $data=mysqli_query($conn,$update);
    if($data){
     ?>
     
        <script type="text/javascript">
            alert("data  updated")
            </script>
            <?php
    }
    else{
        ?>
        <script type="text/javascript">
            alert("data  not saved")
            </script>
            <?php
    }
}
?>
   