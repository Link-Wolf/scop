<div id="top"></div>

<div align="center">
 <a href="https://github.com/Link-Wolf/scop" title="Go to GitHub repo"><img src="https://img.shields.io/static/v1?label=Link-Wolf&message=scop&color=blue&logo=github&style=for-the-badge" alt="Link-Wolf - scop"></a>
 <a href="https://"><img src="https://img.shields.io/badge/42_grade-124_%2F_100-brightgreen?style=for-the-badge" alt="42 grade - 124 / 100"></a>
 <a href="https://"><img src="https://img.shields.io/badge/Year-2024-ffad9b?style=for-the-badge" alt="Year - 2024"></a>
 <a href="https://github.com/Link-Wolf/scop/stargazers"><img src="https://img.shields.io/github/stars/Link-Wolf/scop?style=for-the-badge&color=yellow" alt="stars - scop"></a>
 <a href="https://github.com/Link-Wolf/scop/network/members"><img src="https://img.shields.io/github/forks/Link-Wolf/scop?style=for-the-badge&color=lightgray" alt="forks - scop"></a>
 <a href="https://github.com/Link-Wolf/scop/issues"><img src="https://img.shields.io/github/issues/Link-Wolf/scop?style=for-the-badge&color=orange" alt="issues - scop"></a>
 <a href="https://www.apple.com/macos/" title="Go to Apple homepage"><img src="https://img.shields.io/badge/OS-macOS-blue?logo=apple&logoColor=white&style=for-the-badge&color=9cf" alt="OS - macOS"></a>
</div>

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a>
    <img src="https://www.42mulhouse.fr/wp-content/uploads/2022/06/logo-42-Mulhouse-white.svg" alt="Logo" width="192" height="80">
  </a>

  <h3 align="center">scop</h3>

  <p align="center">
   <em>Basic GPU rendering with OpenGL</em><br/>
    A C++ project to render .obj files using OpenGL
    <br />
    <br />
    <a href="https://github.com/Link-Wolf/scop/issues">Report Bug</a>
    ·
    <a href="https://github.com/Link-Wolf/scop/issues">Request Feature</a>
  </p>
</div>

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->

## About The Project

<div align="center">
  <a>
    <img src="assets/big_human.png" alt="3D render of a human">
  </a>
</div>
</br>
This project aims to use OpenGL to render 3D objects using a GPU.

It takes a .obj file as an argument and renders it in perspective using OpenGL (glew).

GLFW is only used to manage the window and the inputs.

For the input, the following keys are used:

Controls :

-   TAB : Switch between FILL, LINE and POINT mode
-   M : Toggle color_type in triangle mode (monochrome, colors or normale)
-   Arrows : Move the object
-   Mouse scroll : Zoom in/out
-   T : Toggle texturing
-   R : Toggle showroom
-   +/- (numpad ): Distorce the object
-   ESC : Close the window

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- GETTING STARTED -->

## Getting Started

### Prerequisites

C++ compiler (like c++)

-   clang version >= 12.0.0
-   opengl version >= 3.3
-   glfw version >= 3.3.6

### Installation

1. Clone the repo

    ```sh
    git clone https://github.com/Link-Wolf/scop.git
    ```

2. Compile the project

    ```sh
    cd scop; make
    ```

3. Execute it

    ```sh
    ./scop [path_to_obj_file]
    ```

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- USAGE EXAMPLES -->

## Usage

You can render any .obj file using this program (some are [included](./models)). But note that not all features are supported.
Only vertices (`v [x] [y] [z]`) and faces (`f [v1] [v2] [v3] ...`) are supported. The rest is simply ignored.

Here are some examples of rendering the same colored skull using differents modes:

Render only the vertices / Render only the wires linking the vertices / Render the full faces

<div align="center">
 <table>
  <tr>
   <td>
    <img src="assets/skull_dots.png" alt="skull rendered only showing vertices">
   </td>
   <td>
    <img src="assets/skull_wire.png" alt="skull rendered only showing wires linking vertices">
   </td>
   <td>
    <img src="assets/skull_face.png" alt="skull rendered showing full faces">
   </td>
  </tr>
 </table>
 <p>
  Same skull rendered using a "normal shading", and using a beautiful kitten texture
 </p>
 <table>
  <tr>
   <td>
    <img src="assets/skull_normale.png" alt="skull rendered with texture">
   </td>
   <td>
    <img src="assets/skull_text.png" alt="skull rendered with light">
   </td>
  </tr>
 <table>
</div>

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- ROADMAP -->

## Roadmap

-   [x] Add bonus features

See the [open issues](https://github.com/Link-Wolf/scop/issues) for a full list of proposed features (and known issues).

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- CONTRIBUTING -->

## Contributing

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<p align="right">(<a href="#top">back to top</a>)</p>
