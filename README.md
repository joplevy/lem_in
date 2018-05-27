# lem_in

Projet d'algorithmie

L'executable lem-in parse une map decrite comme dans les fichiers /maps/t1.map et maps/t2.map.

Ces fichiers definisent un ensemble de salles, les liaisons entres les salles, et un certain nombre de fourmies a déplacer.

toutes les fourmies doivent aller d'une salle a une autre pendant le moins de tour possible.

Les salles autre que celle de depart et celle d'arrivée ne peuvent contenir qu'une fourmie a la foi.

chaque tour nous pouvons déplacer les differantes fourmies d'une salle a une autre.

L'executble lem_in retourne sous forme de texte l'entrée du programme suivi des mouvements a faire pour déplacer toutes les fourmies à l'arrivée comme ceci 
```
./lem_in < maps/t1.map
5
##start
1 23 3
2 16 7
#commentaire
3 16 3
4 16 5
5 9 3
6 1 5
7 4 8
##end
0 9 5
0-4
0-6
1-3
4-3
5-2
3-5
#autre commentaire
4-2
2-1
7-6
7-2
7-4
6-5

L1-3 L2-2
L1-4 L3-3
L1-0 L2-4 L4-2
L2-0 L3-4 L5-3
L3-0 L4-4
L4-0 L5-4
L5-0
```


L'executable graphical view lisant la sortie de lem_in sur l'entrée standard pour en afficher un appercu plus graphique.

Voici la commande a lancer pour obtenir l'affichage suivant :
```
./lem_in < maps/t1.map | ./graphical_view
```
![alt-text](https://github.com/joplevy/lem_in/blob/master/screen_graph_view.png)
