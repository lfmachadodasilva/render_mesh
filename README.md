# Render Mesh Project

<p>Mesh rendering study using a newer API OpenGL and Shader.</p> 

<p align="center"><img src="image.jpg" width="300px"/></p>

<h3>Used technologies</h3>
<ul>
<li>Visual Studio (vc10)</li>
<li><a href="http://www.tecgraf.puc-rio.br/iup/">IUP</a> (Portable User Interface) </li>
<li><a href="http://www.tecgraf.puc-rio.br/cd/">CD</a> (Canvas Draw)</li>
<li><a href="http://www.tecgraf.puc-rio.br/im/">IM</a> (Image Representation, Storage, Capture and Processing)</li>
<li>VIS (internal library of <a href="http://www.tecgraf.puc-rio.br/">Tecgraf</a>)</li>
<li>OpenGL (version 3.3)</li>
<li><a href="http://glm.g-truc.net/">GLM</a> (OpenGL Mathematics)</li>
<li>Shader (version 3.3)</li>
</ul>

<h3>Main executable</h3>

<p>Using the IUP library was implemented dialog to render PLY (Polygon File Format) models.</p>

<p align="center"><img src="main.png" width="400px"/></p>

<h3>Canvas library</h3>

<p>With VIS and IUP, was developed a library to manage all manipulation and navigation of the scene. Also, with that library is possible to create attached scenes, zoom and others functionalities.</p>

<p align="center"><img src="canvas.png" width="400px"/></p>

<h3>Render library</h3>

<p>The render project/library is the more complex one because is responsible to process all informations by the model and render the scene with the best performance. 
The structure was build to control the render of each type of primitive as: lines, points, triangles and triangles with texture. Another part of this project/library is the selection. 
Using frustum culling and ray tracing algorithm was possible to develop fast and precise selection.</p>

<p align="center"><img src="MainRender.png" width="400px"/></p>

<p align="center"><img src="render.png" width="400px"/></p>

<h3>Future work</h3>
Incorporate those libraries in <a href="http://www.tecgraf.puc-rio.br/sw-anflex.html">Anflex</a> project (already incorporated).

