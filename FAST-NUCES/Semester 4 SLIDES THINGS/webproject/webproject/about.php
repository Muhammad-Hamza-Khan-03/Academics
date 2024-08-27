<!DOCTYPE html>
<html lang="en">

<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <link rel="stylesheet" href="style.css">
  <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@4.6.2/dist/css/bootstrap.min.css">
  <!--bootstap from w3school ! -->
  <link rel="preconnect" href="https://fonts.googleapis.com">
  <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
  <link href="https://fonts.googleapis.com/css2?family=Roboto&display=swap" rel="stylesheet">
 
  <title>Document</title>
</head>

<body>
  <nav class="navbar navbar-expand-lg navbar-dark bg-dark">
    <a class="navbar-brand" href="#">photographypic.com</a>
    <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarSupportedContent"
      aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation">
      <span class="navbar-toggler-icon"></span>
    </button>

    <div class="collapse navbar-collapse" id="navbarSupportedContent">
      <ul class="navbar-nav ml-auto">
        <li class="nav-item active">
          <a class="nav-link" href="index.php">Home <span class="sr-only">(current)</span></a>
        </li>
        <li class="nav-item">
          <a class="nav-link" href="#">Services</a>
        </li>
        <li class="nav-item">
          <a class="nav-link" href="about.php">About</a>
        </li>
        <li class="nav-item">
          <a class="nav-link" href="contact.php">Contact</a>
        </li>
      </ul>
      <form class="form-inline my-2 my-lg-0">
        <input class="form-control mr-sm-2" type="search" placeholder="Search" aria-label="Search">
        <button class="btn btn-outline-success my-2 my-sm-0" type="submit">Search</button>
      </form>
    </div>
  </nav> 

  <div class="jumbotron">
  <h1>Dawood Khawar</h1>
  <p>Photographer Naturelover</p>
  <section class="my-5">
    <div class="py-5">
      <h2 class=" text-center">About us</h2>
    </div>
    <div class="container-fluid">
      <!--to remove scoll bar-->
      <div class="row">
        <!-- large 6 column and 6 medium column and 12 on phone ! -->
        <div class="col-lg-6 col-md-6 col 12">
          <img src="image/gallery-5.jpg" class="img-fluid aboutimg">
        </div>
        <div class="col-lg-6 col-md-6 col 12">
          <h2>I am Photographer</h2>
          <p class="py-3">A photography portfolio is a collection of a photographer's best work, showcasing their skills, style, and unique vision. As a photographer, a well-crafted portfolio is crucial in presenting your work to potential clients, collaborators, and the public.</p>
          <a href="about.php" class="btn btn-success"> See more</a>
        </div>
      </div>
    </div>

  </section>

</div>
<footer>
    <p class="p-3 bg-dark text-white text-center">photographypic123@outlook.com
   </p>
  </footer>
  </body>

</html>