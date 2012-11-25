#include "structures/Structures.h"
#include "structures/Erosion.h"
#include "structures/Dilatation.h"

void Fermeture(int argc, char **argv)
{
 Dilatation(image,imres);
 Erosion(image,imres);
}
