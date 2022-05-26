//
//  main.cpp
//  Xcode12
//
//  Created by Randle Helmslay on 2022/5/24.
//

#include <stdio.h>
#include "rh_math.hpp"
#include "rh_lib.hpp"
#include "rh_lib.h"
#include "rh_color.h"

#include <iostream>


using namespace std;
int main(){
    
//    printf( "<font color=\"#%6x\">RH_COLOR_LAVENDERBLUSH  </font>\n", RH_COLOR_LAVENDERBLUSH   );
//    printf( "<font color=\"#%6x\">RH_COLOR_PALEVIOLATRED  </font>\n", RH_COLOR_PALEVIOLATRED   );
//    printf( "<font color=\"#%6x\">RH_COLOR_HOTPINK        </font>\n", RH_COLOR_HOTPINK         );
//    printf( "<font color=\"#%6x\">RH_COLOR_MEDIUMVIOLATRED</font>\n", RH_COLOR_MEDIUMVIOLATRED );
//    printf( "<font color=\"#%6x\">RH_COLOR_ORCHID         </font>\n", RH_COLOR_ORCHID          );
//    printf( "<font color=\"#%6x\">RH_COLOR_THISTLE        </font>\n", RH_COLOR_THISTLE         );
//    printf( "<font color=\"#%6x\">RH_COLOR_PLUM           </font>\n", RH_COLOR_PLUM            );
//    printf( "<font color=\"#%6x\">RH_COLOR_VOILET         </font>\n", RH_COLOR_VOILET          );
//    printf( "<font color=\"#%6x\">RH_COLOR_DARKVOILET     </font>\n", RH_COLOR_DARKVOILET      );
//    printf( "<font color=\"#%6x\">RH_COLOR_PURPLE         </font>\n", RH_COLOR_PURPLE          );
//    printf( "<font color=\"#%6x\">RH_COLOR_MEDIUMORCHID   </font>\n", RH_COLOR_MEDIUMORCHID    );
//    printf( "<font color=\"#%6x\">RH_COLOR_DARKVIOLET     </font>\n", RH_COLOR_DARKVIOLET      );
//    printf( "<font color=\"#%6x\">RH_COLOR_INDIGO         </font>\n", RH_COLOR_INDIGO          );
//    printf( "<font color=\"#%6x\">RH_COLOR_BLUEVIOLET     </font>\n", RH_COLOR_BLUEVIOLET      );
//    printf( "<font color=\"#%6x\">RH_COLOR_MEDIUMPURPLE   </font>\n", RH_COLOR_MEDIUMPURPLE    );
//    printf( "<font color=\"#%6x\">RH_COLOR_MEDIUMSLATEBLUE</font>\n", RH_COLOR_MEDIUMSLATEBLUE );
//    printf( "<font color=\"#%6x\">RH_COLOR_SLATEBLUE      </font>\n", RH_COLOR_SLATEBLUE       );
//    printf( "<font color=\"#%6x\">RH_COLOR_DARKSLATEBLUE  </font>\n", RH_COLOR_DARKSLATEBLUE   );
//    printf( "<font color=\"#%6x\">RH_COLOR_LAVENDER       </font>\n", RH_COLOR_LAVENDER        );
//    printf( "<font color=\"#%6x\">RH_COLOR_GHOSTWHITE     </font>\n", RH_COLOR_GHOSTWHITE      );
    
    
//    printf( "<font color=\"#%6x\">RH_COLOR_MEDIUMBLUE    </font>\n", RH_COLOR_MEDIUMBLUE     );
//    printf( "<font color=\"#%6x\">RH_COLOR_MIDNIGHTBLUE  </font>\n", RH_COLOR_MIDNIGHTBLUE   );
//    printf( "<font color=\"#%6x\">RH_COLOR_DARKBLUE      </font>\n", RH_COLOR_DARKBLUE       );
//    printf( "<font color=\"#%6x\">RH_COLOR_NAVY          </font>\n", RH_COLOR_NAVY           );
//    printf( "<font color=\"#%6x\">RH_COLOR_ROYALBLUE     </font>\n", RH_COLOR_ROYALBLUE      );
//    printf( "<font color=\"#%6x\">RH_COLOR_CORNFLOWERBLUE</font>\n", RH_COLOR_CORNFLOWERBLUE );
//    printf( "<font color=\"#%6x\">RH_COLOR_LIGHTSTEELBLUE</font>\n", RH_COLOR_LIGHTSTEELBLUE );
//    printf( "<font color=\"#%6x\">RH_COLOR_LIGHTSLATEGRAY</font>\n", RH_COLOR_LIGHTSLATEGRAY );
//    printf( "<font color=\"#%6x\">RH_COLOR_SLATEGRAY     </font>\n", RH_COLOR_SLATEGRAY      );
//    printf( "<font color=\"#%6x\">RH_COLOR_DODGERBLUE    </font>\n", RH_COLOR_DODGERBLUE     );
//    printf( "<font color=\"#%6x\">RH_COLOR_ALICEBLUE     </font>\n", RH_COLOR_ALICEBLUE      );
//    printf( "<font color=\"#%6x\">RH_COLOR_STEELBLUE     </font>\n", RH_COLOR_STEELBLUE      );
//    printf( "<font color=\"#%6x\">RH_COLOR_LIGHTSKYBLUE  </font>\n", RH_COLOR_LIGHTSKYBLUE   );
//    printf( "<font color=\"#%6x\">RH_COLOR_SKYBLUE       </font>\n", RH_COLOR_SKYBLUE        );
//    printf( "<font color=\"#%6x\">RH_COLOR_DEEPSKYBLUE   </font>\n", RH_COLOR_DEEPSKYBLUE    );
//    printf( "<font color=\"#%6x\">RH_COLOR_LIGHTBLUE     </font>\n", RH_COLOR_LIGHTBLUE      );
//    printf( "<font color=\"#%6x\">RH_COLOR_POWDERBLUE    </font>\n", RH_COLOR_POWDERBLUE     );
//    printf( "<font color=\"#%6x\">RH_COLOR_CADETBLUE     </font>\n", RH_COLOR_CADETBLUE      );
//    printf( "<font color=\"#%6x\">RH_COLOR_AZURE         </font>\n", RH_COLOR_AZURE          );
//    printf( "<font color=\"#%6x\">RH_COLOR_LIGHTCYAN     </font>\n", RH_COLOR_LIGHTCYAN      );
//    printf( "<font color=\"#%6x\">RH_COLOR_PALETURQUOISE </font>\n", RH_COLOR_PALETURQUOISE  );
    
    
    printf("<font color=\"#%6x\">RH_COLOR_BLOODYMEAT </font>\n", RH_COLOR_BLOODYMEAT   );
    printf("<font color=\"#%6x\">RH_COLOR_LIGHTCORAL </font>\n", RH_COLOR_LIGHTCORAL   );
    printf("<font color=\"#%6x\">RH_COLOR_ROSEBROWN  </font>\n", RH_COLOR_ROSEBROWN    );
    printf("<font color=\"#%6x\">RH_COLOR_INDIANRED  </font>\n", RH_COLOR_INDIANRED    );
    printf("<font color=\"#%6x\">RH_COLOR_BROWN      </font>\n", RH_COLOR_BROWN        );
    printf("<font color=\"#%6x\">RH_COLOR_FIREBRICK  </font>\n", RH_COLOR_FIREBRICK    );
    printf("<font color=\"#%6x\">RH_COLOR_DARKRED    </font>\n", RH_COLOR_DARKRED      );
    printf("<font color=\"#%6x\">RH_COLOR_MAROON     </font>\n", RH_COLOR_MAROON       );
    
    printf("<font color=\"#%6x\">RH_COLOR_WHITESMOKE </font>\n", RH_COLOR_WHITESMOKE   );
    printf("<font color=\"#%6x\">RH_COLOR_GAINSBORO  </font>\n", RH_COLOR_GAINSBORO    );
    printf("<font color=\"#%6x\">RH_COLOR_LIGHTGRAY  </font>\n", RH_COLOR_LIGHTGRAY    );
    printf("<font color=\"#%6x\">RH_COLOR_SILVER     </font>\n", RH_COLOR_SILVER       );
    printf("<font color=\"#%6x\">RH_COLOR_DARKGRAY   </font>\n", RH_COLOR_DARKGRAY     );
    printf("<font color=\"#%6x\">RH_COLOR_DIMGRAY    </font>\n", RH_COLOR_DIMGRAY      );
    
    printf("<font color=\"#%6x\">RH_COLOR_COAL       </font>\n", RH_COLOR_COAL        );
    printf("<font color=\"#%6x\">RH_COLOR_BLUE       </font>\n", RH_COLOR_BLUE       );
    printf("<font color=\"#%6x\">RH_COLOR_RED        </font>\n", RH_COLOR_RED        );
    printf("<font color=\"#%6x\">RH_COLOR_GREEN      </font>\n", RH_COLOR_GREEN      );
    printf("<font color=\"#%6x\">RH_COLOR_YELLOW     </font>\n", RH_COLOR_YELLOW     );
    printf("<font color=\"#%6x\">RH_COLOR_CYAN       </font>\n", RH_COLOR_CYAN       );
    printf("<font color=\"#%6x\">RH_COLOR_MAGENTA    </font>\n", RH_COLOR_MAGENTA    );
    
    
    
    
    
    
    
    
    
    return 0;
}
























