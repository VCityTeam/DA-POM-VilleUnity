# Installation

## Step 1 - Cloner le dépôt

```bash
git clone https://github.com/VCityTeam/DA-POM.git
```

## Step 2 - Configuration du projet

### Windows

La bibliothèque [LibXML2](http://www.xmlsoft.org/index.html) est fournie dans le dossier [lib/](./lib). Pour résoudre les directives d'includes `#include <libxml/xxx.h>`, il faut indiquer à votre IDE le chemin vers `./lib/libxml2-2.9.3/include/libxml2/` ainsi que le chemin vers les `.lib` : `./lib/libxml2-2.9.3/lib/`.

Il ne reste plus qu'à indiquer à votre IDE les dépendances supplémentaires :
```
libxml2.lib
glu32.lib
```

#### Avec Visual Studio (testé avec vs2017 & vs2019)

Pour démarrer rapidement avec Visual Studio :
* Ouvrir Visual Studio
* (Vous pouvez vous aider de la page [suivante](https://docs.microsoft.com/fr-fr/cpp/build/how-to-create-a-cpp-project-from-existing-code?view=msvc-160))
* Fichier > Nouveau > Projet à partir de code existant
  * Suivez les étapes de l'assistant
  * Dans "Emplacement du fichier projet", mettre le dossier cloné précédemment
  * "Type de projet" : "Projet d'application console"
  * Configuration Debug : rien à rajouter
  * Configuration Release : rien à rajouter
* Sélectionnez la configuration `x64`
* Ensuite, Click droit sur le nom du projet > Propriétés
  * Sélectionnez "Répertoires VC++"
    * Dans "Répertoires Include", rajoutez les chemins ***absolu*** vers ces dossiers :
      * `./lib/libxml2-2.9.3/include/libxml2/`
      * `./lib/gdal-2.0.2/include/`
    * Dans "Répertoires de bibliothèques", rajoutez les chemins ***absolu*** vers ces dossiers :
      * `./lib/libxml2-2.9.3/lib/`
      * `./lib/gdal-2.0.2/lib/`
  * Sous "Éditeurs de liens", sélectionnez "entrée"
    * Dans "Dépendances supplémentaires", rajoutez `libxml2.lib` et `glu32.lib`
* Pour que l'executable ait accès aux `.dll`, rajoutez dans la variable d'environnement `Path` les chemins ***absolu*** vers ces dossiers :
  * `./lib/libxml2-2.9.3/bin/`
  * `./lib/gdal-2.0.2/bin/`
* Pour passer des arguments en ligne de commande dans Visual Studio :
  * Click droit sur le nom du projet > Propriétés
  * Dans l'onglet "Débogage" > "Arguments de la commande" : mettre vos arguments (ex: emplacement de fichier .gml) en séparant les arguments par des espaces

### Linux

Si vous n'avez pas [LibXML2](http://www.xmlsoft.org/index.html) d'installé : (sur Ubuntu)

```bash
sudo apt install libxml2-dev
```

Le répertoire d'include de la bibliothèque sera probablement : `/usr/include/libxml2`.

Ensuite, vous pouvez ouvrir le projet dans votre IDE favori mais la configuration des directives d'include, arguments de la ligne de commande, etc sera spécifique à votre IDE.

