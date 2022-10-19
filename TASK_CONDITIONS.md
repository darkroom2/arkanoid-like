## Task

Your task is to create a simple Arkanoid-like game.

Reference (Arkanoid, 1986): https://www.youtube.com/watch?v=CS5y9CEUl2g

### Rules

* **It is required to use our framework. We do not accept solutions created using other libraries (like SFML, SDL2 etc).
  Functionality provided by Framework should be enough to do all required drawing. You can load TGA, JPG and PNG images
  as sprites with it.**
* **We have included all necessary assets in the folder “Data”. You can use these or any other assets which you want.**
* **Window size should be possible to set from the command-line, e.g.: game -window 800x600**

### Overview

* **The player controls a platform which can move left and right. The goal is to destroy all blocks by deflecting the ball
  with the platform.**

> **_Note:_** it is not required to make level switching for this task (one game level is enough). However, you can make
> more levels if you want.

### Player

* **The player can move a platform using left and right arrow keyboard buttons. Initially the player can choose the angle
  of the ball by pressing the left mouse button (the ball should be launched in the direction of the mouse cursor).**

### Ball

* **The ball moves linearly with a constant speed. It reflects from edges, blocks and the player's platform.**

### Environment

* **The level consists of blocks, which could be destroyed by a single hit. The ball should reflect from blocks after
  their destruction.**

### Win/loss conditions

* **The player loses when the ball is not caught by the platform. Victory can be achieved by destroying all blocks and
  catching the ball with the platform after.**
* **The game should be restarted after victory/loss.**

### Features

* There is an enemy turret, which randomly moves and shoots a player. Bullets spawned by a turret should pass through
  blocks and not destroy them. Game ends if the player is hit by a bullet.
* There are Red blocks, which could be destroyed only when all other blocks have been destroyed. You can use any color
  which you want.
* The first ability (positive) increases the size of the platform and the second one (negative) decreases it by 40%.
  Ability stays active for 20 seconds. Abilities are “stackable”, it means that it is possible to have multiple active
  instances of the same ability. Minimum size is 50%, maximum is 200% of a default size.
* Abilities are dropped when some random blocks are destroyed. A random ability is spawned in the position of a
  destroyed block. Every ability has a collision, so it can fall down if there is no block below. The player should
  “catch” an ability with the platform.

### Restrictions

* **You should not do any changes in launch.cpp/Framework.h as part of a test task.**
* **There is a sample project "Project", you can modify it or create your own.**

### Found Bugs

* cmake not linking sdl2 library
* png files include broken iCCP header

# PL

## Zadanie

Twoim zadaniem jest stworzenie prostej gry podobnej do Arkanoid-a.

Odnośnik (Arkanoid, 1986): https://www.youtube.com/watch?v=CS5y9CEUl2g

### Zasady

* Wymagane jest użycie naszego framework-a. Nie akceptujemy rozwiązań stworzonych przy użyciu innych bibliotek (jak
  SFML, SDL2 itp.). Funkcjonalność dostarczana przez framework powinna być wystarczająca do wykonania wszystkich
  wymaganych rysunków. Możesz załadować obrazy TGA, JPG i PNG jako sprite-y.
* W folderze "Data" umieściliśmy wszystkie niezbędne zasoby. Możesz użyć tych lub innych aktywów, które chcesz.
* Rozmiar okna powinien być możliwy do ustawienia z linii poleceń, np.: game -window 800x600

### Przegląd

* Gracz kontroluje platformę, która może poruszać się w lewo i w prawo. Celem jest zniszczenie wszystkich bloków poprzez
  odbijanie piłki za pomocą platformy.

> **_Uwaga:_** nie jest wymagane robienie poziomów do tego zadania (wystarczy jeden poziom gry). Możesz jednak zrobić
> więcej poziomów, jeśli chcesz.

### Gracz

* Gracz może poruszać się platformą za pomocą przycisków klawiatury ze strzałkami w lewo i w prawo. Początkowo gracz
  może wybrać kąt nachylenia kulki poprzez naciśnięcie lewego przycisku myszy (kulka powinna wystrzelić w kierunku, w
  którym znajduje się kursor myszy).

### Kulka

* Kulka porusza się liniowo ze stałą prędkością. Odbija się od krawędzi, bloków i platformy gracza.

### Środowisko

* Poziom składa się z bloków, które mogą zostać zniszczone przez jedno uderzenie. Kulka powinna odbijać się od bloków po
  ich zniszczeniu.

### Warunki zwycięstwa/przegranej

* Gracz przegrywa, gdy piłka nie zostanie złapana przez platformę. Zwycięstwo można osiągnąć poprzez zniszczenie
  wszystkich bloków i złapanie piłki przez platformę po.
* Po zwycięstwie/przegranej należy ponownie uruchomić grę.

### Mechanizmy

* Istnieje wroga wieżyczka, która losowo porusza się i strzela do gracza. Pociski wystrzelone przez wieżyczkę powinny
  przechodzić przez bloki, a nie je niszczyć. Gra kończy się, jeśli gracz zostanie trafiony przez pocisk.
* Istnieją czerwone bloki, które mogą być zniszczone tylko wtedy, gdy wszystkie inne bloki zostały zniszczone. Możesz
  użyć dowolnego koloru, który chcesz.
* Pierwsza umiejętność (pozytywna) zwiększa rozmiar platformy, a druga (negatywna) zmniejsza go o 40%. Zdolność
  pozostaje aktywna przez 20 sekund. Zdolności są "stackowalne", to znaczy, że można mieć kilka aktywnych instancji tej
  samej zdolności. Minimalny rozmiar to 50%, maksymalny to 200% domyślnego rozmiaru.
* Umiejętności spadają po zniszczeniu kilku losowych bloków. Losowa umiejętność jest tworzona w miejscu zniszczonego
  bloku. Każda umiejętność ma kolizję, więc może spaść, jeśli nie ma pod nią żadnego bloku. Gracz powinien "złapać"
  umiejętność za pomocą platformy.

### Ograniczenia

* Nie powinieneś robić żadnych zmian w launch.cpp/Framework.h jako część zadania testowego.
* Istnieje przykładowy projekt "Project", możesz go zmodyfikować lub stworzyć własny.
