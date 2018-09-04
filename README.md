# Wolf3D

Inspired by the world-famous 90's game of similar naming (which was the first FPS ever). Explore the technique of ray-casting. The goal is to create a dynamic view inside of a maze. How far will you go to create the best game we have ever seen?

Work in progress

from:</br>
banthony</br>
grdalmas</br>
jlobjois consultant en mathématique</br>

# Install and Run (MacOS & Linux only)
git clone https://github.com/banthony42/Wolf3D.git</br>
</br>
cd Wolf3D</br>
</br>
git clone https://github.com/banthony42/libft.git</br>
</br>
make</br>
</br>
./wolf3D ./map/...



# Bugs connus
Game:
  Les fps chutes en mode non texturé, lorsque l'on se rapproche des murs.
  Les map avec spawner sont considéré invalide, surement à cause de la mise à la norme.
  
Map Creator:
  Le clic est ignoré, et la map est dessiné à chaque tour de boucle.
  (surement a cause de la mise a la norme, ou modif de l'enum t_texture)
