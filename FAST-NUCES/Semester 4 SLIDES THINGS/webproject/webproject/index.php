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
 
  <title>myproject</title>
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
          <a class="nav-link" href="servies.php">Services</a>
        </li>
        <li class="nav-item">
          <a class="nav-link" href="about.php">About</a>
        </li>
        <li class="nav-item">
          <a class="nav-link" href="#">Contact</a>
        </li>
      </ul>
      <form class="form-inline my-2 my-lg-0">
        <input class="form-control mr-sm-2" type="search" placeholder="Search" aria-label="Search">
        <button class="btn btn-outline-success my-2 my-sm-0" type="submit">Search</button>
      </form>
    </div>
  </nav> <!-- nav bar taken from bootstap and edit it -->
  <div id="demo" class="carousel slide" data-ride="carousel">
    <ul class="carousel-indicators">
      <li data-target="#demo" data-slide-to="0" class="active"></li>
      <li data-target="#demo" data-slide-to="1"></li>
      <li data-target="#demo" data-slide-to="2"></li>
    </ul>
    <div class="carousel-inner"> <?php //carousel taken from w3school ?>
      <div class="carousel-item active">
        <img src="image/gallery-1.jpg" alt="Los Angeles" width="1100" height="500">
        <div class="carousel-caption">
          <h3>Los Angeles</h3>
          <p>We had such a great time in LA!</p>
        </div>
      </div>
      <div class="carousel-item">
        <img src="image/gallery-12.jpg" alt="Chicago" width="1100" height="500">
        <div class="carousel-caption">
          <h3>Chicago</h3>
          <p>Thank you, Chicago!</p>
        </div>
      </div>
      <div class="carousel-item">
        <img src="image/gallery-5.jpg" alt="New York" width="1100" height="500">
        <div class="carousel-caption">
          <h3>North America</h3>
          <p>We love Mountain</p>
        </div>
      </div>
    </div>
    <a class="carousel-control-prev" href="#demo" data-slide="prev">
      <span class="carousel-control-prev-icon"></span>
    </a>
    <a class="carousel-control-next" href="#demo" data-slide="next">
      <span class="carousel-control-next-icon"></span>
    </a>
  </div>
  <section class="my-5">
    <div class="py-5">
      <h2 class=" text-center">About us</h2>
    </div>
    <div class="container-fluid">
      <!--to remove scoll bar-->
      <div class="row">
        <!-- large 6 column and 6 medium column and 12 on phone ! -->
        <div class="col-lg-6 col-md-6 col 12">
          <img src="image/g10.png" class="img-fluid aboutimg">
        </div>
        <div class="col-lg-6 col-md-6 col 12">
          <h2>I am Photographer</h2>
          <p class="py-3">A photography portfolio is a collection of a photographer's best work, showcasing their skills, style, and unique vision. As a photographer, a well-crafted portfolio is crucial in presenting your work to potential clients, collaborators, and the public.</p>
          <a href="about.php" class="btn btn-success"> See more</a>
        </div>
      </div>
    </div>

  </section>

  <section class="my-5">
    <div class="py-5">
      <h3 class=" text-center">Our services</h3>
    </div>
    <div class="container-fluid">
      <div class="row">
        <div class="col-lg-4 col-md-8 col-12">
          <div class="card" style="width:400px">
            <img class="card-img-top" src="image/gallery-20.jpg" alt="Card image">
            <div class="card-body">
              <h4 class="card-title">Wild Life </h4>
              <p class="card-text">wildlife captures the beauty and diversity of nature, and offers a glimpse into the lives of animals and their habitats.</p>
              <a href="#" class="btn btn-primary">See Profile</a>
            </div>
          </div>
        </div>
        <div class="col-lg-4 col-md-4 col-12">
          <div class="card" style="width:400px" ">
            <img class="card-img-top" src="image/gallery-15.jpg" alt="Card image">
            <div class="card-body">
              <h4 class="card-title">Nature </h4>
              <p class="card-text"> the beauty and diversity of the natural world and provides a visual representation of the interconnectedness of all living things.</p>
              <a href="#" class="btn btn-primary">See Profile</a>
            </div>
          </div>
        </div>
        <div class="col-lg- col-md-4 col-12">
          <div class="card" style="width:400px">
            <img class="card-img-top" src="image/gallery-17.jpg" alt="Card image">
            <div class="card-body">
              <h4 class="card-title">Antique building </h4>
              <p class="card-text">This sultry coastal city is a must-see on any Latin America bucket list .</p>
              <a href="#" class="btn btn-primary">See Profile</a>
            </div>
          </div>
        </div>
      </div>
    </div>
  </section>
  <!--cards from bootstrap !-->

  <section class="my-5">
    <div class="py-5">
      <h3 class=" text-center">Our Gallery</h3>

    </div>
    <div>
      <div class="container-fluid">
        <div class="row">
          <div class="col-lg- col-md-4 col-12">
            <img src="image/g1.jpg" clsss="img-fluid pb-4">
          </div>
          <div class="col-lg- col-md-4 col-12">
            <img src="image/g2.jpg" clsss="img-fluid pb-4">
          </div>
          <div class="col-lg- col-md-4 col-12">
            <img src="image/g5.jpg" clsss="img-fluid pb-4">
          </div>
          <div class="col-lg- col-md-4 col-12">
            <img src="image/g4.jpg" clsss="img-fluid pb-4">
          </div>
          <div class="col-lg- col-md-4 col-12">
            <img src="image/g3.jpg" clsss="img-fluid pb-4">
          </div>
          <div class="col-lg- col-md-4 col-12">
            <img src="image/g7.jpg" clsss="img-fluid pb-4">
          </div>
          <div class="col-lg- col-md-4 col-12">
            <img src="image/g9.jpg" clsss="img-fluid pb-4">
          </div>
          <div class="col-lg- col-md-4 col-12">
            <img src="image/g8.jpg" clsss="img-fluid pb-4">
          </div>
          <div class="col-lg- col-md-4 col-12">
            <img src="image/g104.jpg" clsss="img-fluid pb-4">
          </div>


        </div>
      </div>
  </section>

  <section class="my-5">
    <div class="py-5">
      <h3 class=" text-center">Contacts Us</h3>
      <div class="w-50 m-auto">
        <form action="userinfo.php" method="post">
          <div class="form-group">
            <label>username</label>
            <input type="text" name="user" autocomplete="off" class="form-control">
          </div>
          <div class="form-group">
            <label>Email</label>
            <input type="text" name="email" autocomplete="off" class="form-control">
          </div>
          <div class="form-group">
            <label>phone</label>
            <input type="text" name="phone" autocomplete="off" class="form-control">

            <div class="form-group">
              <label>comment</label>

              <textarea class="form-control" name="comment"></textarea>
              <div>
                <input type="submit" class="btn btn-secondary" name="submit" value="Submit">
              </div>
              <br>
              <div><a href="view.php" class="btn btn-primary">View</a></div>
        </form>
      </div>
    </div>
  </section>
  <footer>
    <p class="p-3 bg-dark text-white text-center">photographypic123@outlook.com
   </p>
  </footer>
  <script src="https://cdn.jsdelivr.net/npm/jquery@3.6.1/dist/jquery.slim.min.js"></script>
  <script src="https://cdn.jsdelivr.net/npm/popper.js@1.16.1/dist/umd/popper.min.js"></script>
  <script src="https://cdn.jsdelivr.net/npm/bootstrap@4.6.2/dist/js/bootstrap.bundle.min.js"></script>
  </body>

  </html>

