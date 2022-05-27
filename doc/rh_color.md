# RH_COLOR

## Overview

This library provides several macros upon color synthesis. The default color depth is 24bit long under the LSB order of Red, Green and Blue. It can be converted to 16bit compressed mode as well. Macros that extracts RGB element are also included. Please note that the alpha channel is **NOT** considered and it will be lost while using the following method.



## Macro Manual Reference

---

### `RH_RED` |`RH_GREEN` | `RH_BLUE`

- **Example**

  ```C
  assert( RH_RED( RH_COLOR_RED )==0xff ); // Because "RH_COLOR_RED" is made up by (0xff, 0x00, 0x00)
  assert( RH_RED( RH_COLOR_RED )==0x00 );
  assert( RH_RED( RH_COLOR_RED )==0x00 );
  ```

  ```C
  assert( RH_RED  ( RH_COLOR_YELLOW )==0xff ); // Because "RH_COLOR_YELLOW" is made up by (0xff, 0xff, 0x00)
  assert( RH_GREEN( RH_COLOR_YELLOW )==0xff );
  assert( RH_BLUE ( RH_COLOR_YELLOW )==0x00 );
  ```

  

---

### `RH_MAKE_COLOR` | `RH_MAKE_COLOR_16BIT` | `RH_MAKE_COLOR_24BIT`

- **Note**

  `RH_MAKE_COLOR_16BIT( R_255, G_255, B_255)` takes three 8-bit color channels and return RGB565 color value. That is 5-bit for red and blue channels and 6-bit for green channel.

  `RH_MAKE_COLOR_24BIT( R_255, G_255, B_255)` typically do nothing but stay with the context. For each channel, it has to be 8-bit long.

  `RH_MAKE_COLOR( R_255, G_255, B_255)` can be selected as one of those above. That determined the color depth of pre-defined color macro.

- **Example**

  ```C
  uint32_t white = RH_MAKE_COLOR_24BIT( 255, 255, 255);
  uint16_t black = RH_MAKE_COLOR_16BIT(   0,   0,   0);
  ```

  

## Macro Color Preview

| Red Basis                                                  | Blue Basis                                                   | Green Basis                                                  |
| ---------------------------------------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| ![ff0000](./rh_color/ff0000.png)`RH_COLOR_RED           `  | ![0000ff](./rh_color/0000ff.png)`RH_COLOR_BLUE          `    | ![00ff00](./rh_color/00ff00.png)`RH_COLOR_GREEN         `    |
| ![ff6347](./rh_color/ff6347.png)`RH_COLOR_TOMATO         ` | ![6a5acd](./rh_color/6a5acd.png)`RH_COLOR_SLATEBLUE      `   | ![00ffff](./rh_color/00ffff.png)`RH_COLOR_CYAN          `    |
| ![ff4500](./rh_color/ff4500.png)`RH_COLOR_ORANGERED      ` | ![0000cd](./rh_color/0000cd.png)`RH_COLOR_MEDIUMBLUE    `    | ![00ffff](./rh_color/00ffff.png)`RH_COLOR_AQUA             ` |
| ![db7093](./rh_color/db7093.png)`RH_COLOR_PALEVIOLATRED  ` | ![191970](./rh_color/191970.png)`RH_COLOR_MIDNIGHTBLUE  `    | ![00ced1](./rh_color/00ced1.png)`RH_COLOR_DARKTURQUOISE    ` |
| ![ff7f50](./rh_color/ff7f50.png)`RH_COLOR_CORAL          ` | ![00008b](./rh_color/00008b.png)`RH_COLOR_DARKBLUE      `    | ![2f4f4f](./rh_color/2f4f4f.png)`RH_COLOR_DARKSLATEGRAY    ` |
| ![ff69b4](./rh_color/ff69b4.png)`RH_COLOR_HOTPINK        ` | ![000080](./rh_color/000080.png)`RH_COLOR_NAVY          `    | ![008b8b](./rh_color/008b8b.png)`RH_COLOR_DARKCYAN         ` |
| ![fff0f5](./rh_color/fff0f5.png)`RH_COLOR_LAVENDERBLUSH  ` | ![4169e1](./rh_color/4169e1.png)`RH_COLOR_ROYALBLUE     `    | ![008080](./rh_color/008080.png)`RH_COLOR_TEAL             ` |
| ![d8bfd8](./rh_color/d8bfd8.png)`RH_COLOR_THISTLE        ` | ![6495ed](./rh_color/6495ed.png)`RH_COLOR_CORNFLOWERBLUE`    | ![48d1cc](./rh_color/48d1cc.png)`RH_COLOR_MEDIUMTURQUOISE  ` |
| ![dda0dd](./rh_color/dda0dd.png)`RH_COLOR_PLUM           ` | ![b0c4de](./rh_color/b0c4de.png)`RH_COLOR_LIGHTSTEELBLUE`    | ![20b2aa](./rh_color/20b2aa.png)`RH_COLOR_LIGHTSEEGREEN    ` |
| ![da70d6](./rh_color/da70d6.png)`RH_COLOR_VOILET         ` | ![778899](./rh_color/778899.png)`RH_COLOR_LIGHTSLATEGRAY`    | ![40e0d0](./rh_color/40e0d0.png)`RH_COLOR_TURQUOISE        ` |
| ![c71585](./rh_color/c71585.png)`RH_COLOR_MEDIUMVIOLATRED` | ![708090](./rh_color/708090.png)`RH_COLOR_SLATEGRAY     `    | ![7fffd4](./rh_color/7fffd4.png)`RH_COLOR_AQUAMARINE       ` |
| ![da70d6](./rh_color/da70d6.png)`RH_COLOR_ORCHID         ` | ![7b68ee](./rh_color/7b68ee.png)`RH_COLOR_MEDIUMSLATEBLUE`   | ![228b22](./rh_color/228b22.png)`RH_COLOR_FORESTGREEN      ` |
| ![800080](./rh_color/800080.png)`RH_COLOR_PURPLE         ` | ![1e72ff](./rh_color/1e72ff.png)`RH_COLOR_DODGERBLUE    `    | ![66cdaa](./rh_color/66cdaa.png)`RH_COLOR_MEDIUMAQUAMARINE ` |
| ![ff00ff](./rh_color/ff00ff.png)`RH_COLOR_MEDIUMORCHID   ` | ![f0f8ff](./rh_color/f0f8ff.png)`RH_COLOR_ALICEBLUE     `    | ![00fa9a](./rh_color/00fa9a.png)`RH_COLOR_MEDIUMSPRINGGREEN` |
| ![9400d3](./rh_color/9400d3.png)`RH_COLOR_DARKVIOLET     ` | ![4682b4](./rh_color/4682b4.png)`RH_COLOR_STEELBLUE     `    | ![00ff7f](./rh_color/00ff7f.png)`RH_COLOR_SPRINGGREEN      ` |
| ![4b0082](./rh_color/4b0082.png)`RH_COLOR_INDIGO         ` | ![87cefa](./rh_color/87cefa.png)`RH_COLOR_LIGHTSKYBLUE  `    | ![3cb371](./rh_color/3cb371.png)`RH_COLOR_MEDIUMSEEGREEN   ` |
| ![8a2be2](./rh_color/8a2be2.png)`RH_COLOR_BLUEVIOLET     ` | ![87ceeb](./rh_color/87ceeb.png)`RH_COLOR_SKYBLUE       `    | ![2e8b57](./rh_color/2e8b57.png)`RH_COLOR_SEEGREEN         ` |
| ![9370db](./rh_color/9370db.png)`RH_COLOR_MEDIUMPURPLE   ` | ![00bfff](./rh_color/00bfff.png)`RH_COLOR_DEEPSKYBLUE   `    | ![90ee90](./rh_color/90ee90.png)`RH_COLOR_LIGHTGREEN       ` |
| ![ff00ff](./rh_color/ff00ff.png)`RH_COLOR_MAGENTA       `  | ![add8e6](./rh_color/add8e6.png)`RH_COLOR_LIGHTBLUE     `    | ![98fb98](./rh_color/98fb98.png)`RH_COLOR_PALEGREEN        ` |
| ![ff00ff](./rh_color/ff00ff.png)`RH_COLOR_DARKVOILET     ` | ![b0e0e6](./rh_color/b0e0e6.png)`RH_COLOR_POWDERBLUE    `    | ![8fbc8f](./rh_color/8fbc8f.png)`RH_COLOR_DARKSEEGREEN     ` |
| ![483d8b](./rh_color/483d8b.png)`RH_COLOR_DARKSLATEBLUE  ` | ![5f9ea0](./rh_color/5f9ea0.png)`RH_COLOR_CADETBLUE     `    | ![32cd32](./rh_color/32cd32.png)`RH_COLOR_LIME             ` |
| ![e6e6fa](./rh_color/e6e6fa.png)`RH_COLOR_LAVENDER       ` | ![f5ffff](./rh_color/f5ffff.png)`RH_COLOR_AZURE         `    | ![7fff00](./rh_color/7fff00.png)`RH_COLOR_CHARTREUSE       ` |
| ![f8f8ff](./rh_color/f8f8ff.png)`RH_COLOR_GHOSTWHITE     ` | ![f0ffff](./rh_color/f0ffff.png)`RH_COLOR_LIGHTCYAN     `    | ![afeeee](./rh_color/afeeee.png)`RH_COLOR_PALETURQUOISE    ` |
| ![ffe4b5](./rh_color/ffe4b5.png)`RH_COLOR_MOCCASIN       ` | ![fa8072](./rh_color/fa8072.png)`RH_COLOR_BLOODYMEAT    `    | ![228b22](./rh_color/228b22.png)`RH_COLOR_OLIVEDRAB        ` |
| ![ffa500](./rh_color/ffa500.png)`RH_COLOR_ORANGE         ` | ![f08080](./rh_color/f08080.png)`RH_COLOR_LIGHTCORAL    `    | ![7cfc00](./rh_color/7cfc00.png)`RH_COLOR_LAWNGREEN        ` |
| ![ffefd5](./rh_color/ffefd5.png)`RH_COLOR_PAPAYAWHIP     ` | ![bc8f8f](./rh_color/bc8f8f.png)`RH_COLOR_ROSEBROWN     `    | ![adff2f](./rh_color/adff2f.png)`RH_COLOR_GREENYELLOW      ` |
| ![ffebcd](./rh_color/ffebcd.png)`RH_COLOR_BLANCHEDALMOND ` | ![cd5c5c](./rh_color/cd5c5c.png)`RH_COLOR_INDIANRED     `    | ![556b2f](./rh_color/556b2f.png)`RH_COLOR_DARKOLIVEGREEN   ` |
| ![ffdead](./rh_color/ffdead.png)`RH_COLOR_NAVAJOWHITE    ` | ![a52a2a](./rh_color/a52a2a.png)`RH_COLOR_BROWN         `    | ![9acd32](./rh_color/9acd32.png)`RH_COLOR_YELLOWGREEN      ` |
| ![faebd7](./rh_color/faebd7.png)`RH_COLOR_ANTIQUEWHITE   ` | ![b22222](./rh_color/b22222.png)`RH_COLOR_FIREBRICK     `    | ![228b22](./rh_color/228b22.png)`RH_COLOR_LIGHTRODYELLOW   ` |
| ![d2b48c](./rh_color/d2b48c.png)`RH_COLOR_TAN            ` | ![8b0000](./rh_color/8b0000.png)`RH_COLOR_DARKRED       `    | ![f5f5dc](./rh_color/f5f5dc.png)`RH_COLOR_BEIGE            ` |
| ![deb887](./rh_color/deb887.png)`RH_COLOR_BURLYWOOD      ` | ![800000](./rh_color/800000.png)`RH_COLOR_MAROON        `    | ![fff8dc](./rh_color/fff8dc.png)`RH_COLOR_CORNMILK         ` |
| ![ffe4c4](./rh_color/ffe4c4.png)`RH_COLOR_BISQUE         ` | ![f5f5f5](./rh_color/f5f5f5.png)`RH_COLOR_WHITESMOKE    `    | ![fffff0](./rh_color/fffff0.png)`RH_COLOR_IVORY            ` |
| ![ff8c00](./rh_color/ff8c00.png)`RH_COLOR_DARKORANGE     ` | ![dcdcdc](./rh_color/dcdcdc.png)`RH_COLOR_GAINSBORO     `    | ![fffacd](./rh_color/fffacd.png)`RH_COLOR_LEMONCHIFFON     ` |
| ![fff0e6](./rh_color/fff0e6.png)`RH_COLOR_LINEN          ` | ![d3d3d3](./rh_color/d3d3d3.png)`RH_COLOR_LIGHTGRAY     `    | ![eee8aa](./rh_color/eee8aa.png)`RH_COLOR_PALEGOLDROD      ` |
| ![cd853f](./rh_color/cd853f.png)`RH_COLOR_PERU           ` | ![c0c0c0](./rh_color/c0c0c0.png)`RH_COLOR_SILVER        `    | ![bdb76b](./rh_color/bdb76b.png)`RH_COLOR_DARKKHAKI        ` |
| ![f4a460](./rh_color/f4a460.png)`RH_COLOR_SANDYBROWN     ` | ![494949](./rh_color/494949.png)`RH_COLOR_DARKGRAY      `    | ![ffff00](./rh_color/ffff00.png)`RH_COLOR_YELLOW        `    |
| ![d2691e](./rh_color/d2691e.png)`RH_COLOR_CHOCOLATE      ` | ![363636](./rh_color/363636.png)`RH_COLOR_DIMGRAY       `    | ![f0e68c](./rh_color/f0e68c.png)`RH_COLOR_KHAKI            ` |
| ![fff5ee](./rh_color/fff5ee.png)`RH_COLOR_SEASHELL       ` | ![222322](./rh_color/222322.png)`RH_COLOR_COAL          `    | ![ffd700](./rh_color/ffd700.png)`RH_COLOR_GOLDEN           ` |
| ![ffe4e1](./rh_color/ffe4e1.png)`RH_COLOR_MISTYROSE      ` | ![f5deb3](./rh_color/f5deb3.png)`RH_COLOR_WHEAT            ` | ![daa520](./rh_color/daa520.png)`RH_COLOR_GOLDROD          ` |
| ![a0522d](./rh_color/a0522d.png)`RH_COLOR_SIENNA         ` | ![fdf5e6](./rh_color/fdf5e6.png)`RH_COLOR_OLDLACE          ` | ![808000](./rh_color/808000.png)`RH_COLOR_OLIVE            ` |
| ![ffa07a](./rh_color/ffa07a.png)`RH_COLOR_SALMON         ` | ![fffaf0](./rh_color/fffaf0.png)`RH_COLOR_FLORALWHITE      ` | ![b8860b](./rh_color/b8860b.png)`RH_COLOR_DARKGOLDROD      ` |

























