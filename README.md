# MS_4
Miestone 4

Aufgabe 1:
  Es gibt ein zweidimensionales Array "pixelValues" in dem für jeden Pixel ein Wert gespeichert wird, zu Beginn wird das Array mit Nullen gefüllt. Das Array wird mit der Größe 100x100 erstellt. Wird die Zeichenfläche auf kleiner als 100x100 eingestellt, wird nur die obere linke Ecke beschrieben. Es gibt einen Slider mit dem sich die Größe der "Pixel" einstellen lässt, Dadurch wird die größe der Pixel auf der Zeichenfläche geändert. Es gibt zwei Slider um die Höhe und Breite der Zeichenfläche einzustellen. Damit keine halben Pixel angezeigt werden, wird nachdem der Nutzer auf den Button "apply" drückt die nächst kleinere Zahl gesucht sodass nur ganze Pixel angezeigt werden.

  a) Das Widget wird erstellt, und die Zeichenfläche wird in Pixel eingeteilt.
     Es kann darauf gemalt werden, und die Größe der zeichenfläche ist in Höhe und Breite variabel.
     TODO: Es muss möglich sein die Höhe und Breite in Pixeln einzustellen, oder alternativ einen Button erstellen welcher die Zeichenfläche  
     auf 28 mal 28 Pixel einstellt. 
     
  b) Bei einem Klick auf die Zeichenfläche wird der geklickte Pixel schwarz, und seine Position im Array wird auf 1 gesetzt, die angrenzenden 
     Pixel werden im Array auf +0,25 gesetzt, sofern sie nicht bereits 1 sind. 
     Mit Geklickter Maus lässt sich auch per Bewegung malen.
    
  c) Es muss noch eine Funktion implementiert werden, mit welcher Bilder importiert werden können, und auf der Zeichenfläche angezeigt werden.
  
  d)Es gibt einen Button "clear" mit welchem die Zeichenfläche geleert wird.
  
  
