

#include <stddef.h>


#ifndef RH_COLOR
#define RH_COLOR


#define RH_MAKE_COLOR_16BIT(R_255,G_255,B_255)    (uint16_t)((((R_255)>>3)<<11)|(((G_255)>>2)<<5)|((B_255)>>3))
#define RH_MAKE_COLOR_24BIT(R_255,G_255,B_255)    (uint32_t)((((R_255)&0xff)<<16)|(((G_255)&0xff)<<8)|((B_255)&0xff))
#define RH_MAKE_COLOR(R_255,G_255,B_255)          (uint32_t)((((R_255)&0xff)<<16)|(((G_255)&0xff)<<8)|((B_255)&0xff))

#define RH_RED(x)                                 (((x)&0x00ff0000)>>16)
#define RH_GREEN(x)                               (((x)&0x0000ff00)>>8)
#define RH_BLUE(x)                                (((x)&0x000000ff)   )
#define RH_RGB565(x)                              (uint16_t)((((RH_RED(x))>>3)<<11)|(((RH_GREEN(x))>>2)<<5)|((RH_BLUE(x))>>3))
#define RH_RGB888(x)                              (x)

// Standard
#define RH_COLOR_WHITE                        (RH_MAKE_COLOR(255,255,255))  // 白色
#define RH_COLOR_BLACK                        (RH_MAKE_COLOR(  0,  0,  0))  // 黑色
           
#define RH_COLOR_BLUE                         (RH_MAKE_COLOR(  0,  0,255))  // 蓝色
#define RH_COLOR_RED                          (RH_MAKE_COLOR(255,  0,  0))  // 红色
#define RH_COLOR_GREEN                        (RH_MAKE_COLOR(  0,255,  0))  // 绿色
#define RH_COLOR_YELLOW                       (RH_MAKE_COLOR(255,255,  0))  // 黄色
#define RH_COLOR_CYAN                         (RH_MAKE_COLOR(  0,255,255))  // 青色
#define RH_COLOR_MAGENTA                      (RH_MAKE_COLOR(255,  0,255))  // 洋紫
           
// Red-Blue Series
#define RH_COLOR_PINK                         (RH_MAKE_COLOR(255,192,203))  // 粉红
#define RH_COLOR_CRIMSON                      (RH_MAKE_COLOR(220, 20, 60))  // 猩红
#define RH_COLOR_LAVENDERBLUSH                (RH_MAKE_COLOR(255,240,245))  // 苍白紫罗兰红
#define RH_COLOR_PALEVIOLATRED                (RH_MAKE_COLOR(219,112,147))  // 羞涩淡紫红
#define RH_COLOR_HOTPINK                      (RH_MAKE_COLOR(255,105,180))  // 热情粉红
#define RH_COLOR_MEDIUMVIOLATRED              (RH_MAKE_COLOR(199, 21,133))  // 适中紫罗兰
#define RH_COLOR_ORCHID                       (RH_MAKE_COLOR(218,112,214))  // 兰花紫
#define RH_COLOR_THISTLE                      (RH_MAKE_COLOR(216,191,216))  // 苍紫
#define RH_COLOR_PLUM                         (RH_MAKE_COLOR(221,160,221))  // 轻紫
#define RH_COLOR_VOILET                       (RH_MAKE_COLOR(218,112,214))  // 紫罗兰
#define RH_COLOR_DARKVOILET                   (RH_MAKE_COLOR(255,  0,255))  // 紫红
#define RH_COLOR_PURPLE                       (RH_MAKE_COLOR(128,  0,128))  // 紫
#define RH_COLOR_MEDIUMORCHID                 (RH_MAKE_COLOR(255,  0,255))  // 适中兰花紫
#define RH_COLOR_DARKVIOLET                   (RH_MAKE_COLOR(148,  0,211))  // 深紫罗兰
#define RH_COLOR_INDIGO                       (RH_MAKE_COLOR( 75,  0,130))  // 靓青
#define RH_COLOR_BLUEVIOLET                   (RH_MAKE_COLOR(138, 43,226))  // 蓝紫罗兰
#define RH_COLOR_MEDIUMPURPLE                 (RH_MAKE_COLOR(147,112,219))  // 适中紫
#define RH_COLOR_MEDIUMSLATEBLUE              (RH_MAKE_COLOR(123,104,238))  // 适中板岩蓝
#define RH_COLOR_SLATEBLUE                    (RH_MAKE_COLOR(106, 90,205))  // 板岩蓝
#define RH_COLOR_DARKSLATEBLUE                (RH_MAKE_COLOR( 72, 61,139))  // 深板岩蓝
#define RH_COLOR_LAVENDER                     (RH_MAKE_COLOR(230,230,250))  // 薰衣草淡
#define RH_COLOR_GHOSTWHITE                   (RH_MAKE_COLOR(248,248,255))  // 幽灵白
           
// Blue-Green Series
#define RH_COLOR_MEDIUMBLUE                   (RH_MAKE_COLOR(  0,  0,205))  // 适中蓝
#define RH_COLOR_MIDNIGHTBLUE                 (RH_MAKE_COLOR( 25, 25,112))  // 午夜蓝
#define RH_COLOR_DARKBLUE                     (RH_MAKE_COLOR(  0,  0,139))  // 深蓝
#define RH_COLOR_NAVY                         (RH_MAKE_COLOR(  0,  0,128))  // 海军蓝
#define RH_COLOR_ROYALBLUE                    (RH_MAKE_COLOR( 65,105,225))  // 皇家蓝
#define RH_COLOR_CORNFLOWERBLUE               (RH_MAKE_COLOR(100,149,237))  // 矢车菊蓝
#define RH_COLOR_LIGHTSTEELBLUE               (RH_MAKE_COLOR(176,196,222))  // 淡钢蓝
#define RH_COLOR_LIGHTSLATEGRAY               (RH_MAKE_COLOR(119,136,153))  // 浅板岩灰
#define RH_COLOR_SLATEGRAY                    (RH_MAKE_COLOR(112,128,144))  // 石板灰
#define RH_COLOR_DODGERBLUE                   (RH_MAKE_COLOR( 30,114,255))  // 道奇蓝
#define RH_COLOR_ALICEBLUE                    (RH_MAKE_COLOR(240,248,255))  // 爱丽丝蓝
#define RH_COLOR_STEELBLUE                    (RH_MAKE_COLOR( 70,130,180))  // 钢蓝
#define RH_COLOR_LIGHTSKYBLUE                 (RH_MAKE_COLOR(135,206,250))  // 淡天蓝
#define RH_COLOR_SKYBLUE                      (RH_MAKE_COLOR(135,206,235))  // 天蓝
#define RH_COLOR_DEEPSKYBLUE                  (RH_MAKE_COLOR(  0,191,255))  // 深天蓝
#define RH_COLOR_LIGHTBLUE                    (RH_MAKE_COLOR(173,216,230))  // 淡蓝
#define RH_COLOR_POWDERBLUE                   (RH_MAKE_COLOR(176,224,230))  // 火药蓝
#define RH_COLOR_CADETBLUE                    (RH_MAKE_COLOR( 95,158,160))  // 军校蓝
#define RH_COLOR_AZURE                        (RH_MAKE_COLOR(245,255,255))  // 蔚蓝
#define RH_COLOR_LIGHTCYAN                    (RH_MAKE_COLOR(240,255,255))  // 淡青
#define RH_COLOR_PALETURQUOISE                (RH_MAKE_COLOR(175,238,238))  // 苍白宝石绿
#define RH_COLOR_AQUA                         (RH_MAKE_COLOR(  0,255,255))  // 水绿
#define RH_COLOR_DARKTURQUOISE                (RH_MAKE_COLOR(  0,206,209))  // 深宝石绿
#define RH_COLOR_DARKSLATEGRAY                (RH_MAKE_COLOR( 47, 79, 79))  // 深石板灰
#define RH_COLOR_DARKCYAN                     (RH_MAKE_COLOR(  0,139,139))  // 深青色
#define RH_COLOR_TEAL                         (RH_MAKE_COLOR(  0,128,128))  // 水鸭色
#define RH_COLOR_MEDIUMTURQUOISE              (RH_MAKE_COLOR( 72,209,204))  // 适中宝石绿
#define RH_COLOR_LIGHTSEEGREEN                (RH_MAKE_COLOR( 32,178,170))  // 浅海样绿
#define RH_COLOR_TURQUOISE                    (RH_MAKE_COLOR( 64,224,208))  // 宝石绿
#define RH_COLOR_AQUAMARINE                   (RH_MAKE_COLOR(127,255,212))  // 碧绿
#define RH_COLOR_MEDIUMAQUAMARINE             (RH_MAKE_COLOR(102,205,170))  // 适中碧绿
#define RH_COLOR_MEDIUMSPRINGGREEN            (RH_MAKE_COLOR(  0,250,154))  // 适中春天绿
#define RH_COLOR_SPRINGGREEN                  (RH_MAKE_COLOR(  0,255,127))  // 春天绿
#define RH_COLOR_MEDIUMSEEGREEN               (RH_MAKE_COLOR( 60,179,113))  // 适中海洋绿
#define RH_COLOR_SEEGREEN                     (RH_MAKE_COLOR( 46,139, 87))  // 海洋绿
#define RH_COLOR_LIGHTGREEN                   (RH_MAKE_COLOR(144,238,144))  // 浅绿
#define RH_COLOR_PALEGREEN                    (RH_MAKE_COLOR(152,251,152))  // 苍白绿
#define RH_COLOR_DARKSEEGREEN                 (RH_MAKE_COLOR(143,188,143))  // 深海洋绿
#define RH_COLOR_LIME                         (RH_MAKE_COLOR( 50,205, 50))  // 莱姆色
#define RH_COLOR_CHARTREUSE                   (RH_MAKE_COLOR(127,255,  0))  // 查特酒绿
           
// Green-RED Series
#define RH_COLOR_FORESTGREEN                  (RH_MAKE_COLOR( 34,139, 34))  // 森林绿
#define RH_COLOR_LAWNGREEN                    (RH_MAKE_COLOR(124,252,  0))  // 草坪绿
#define RH_COLOR_GREENYELLOW                  (RH_MAKE_COLOR(173,255, 47))  // 绿黄
#define RH_COLOR_DARKOLIVEGREEN               (RH_MAKE_COLOR( 85,107, 47))  // 深橄榄绿
#define RH_COLOR_YELLOWGREEN                  (RH_MAKE_COLOR(154,205, 50))  // 黄绿
#define RH_COLOR_OLIVEDRAB                    (RH_MAKE_COLOR( 34,139, 34))  // 橄榄褐
#define RH_COLOR_BEIGE                        (RH_MAKE_COLOR(245,245,220))  // 米色
#define RH_COLOR_LIGHTRODYELLOW               (RH_MAKE_COLOR( 34,139, 34))  // 浅秋黄
#define RH_COLOR_IVORY                        (RH_MAKE_COLOR(255,255,240))  // 象牙白
#define RH_COLOR_OLIVE                        (RH_MAKE_COLOR(128,128,  0))  // 橄榄
#define RH_COLOR_DARKKHAKI                    (RH_MAKE_COLOR(189,183,107))  // 深卡其布
#define RH_COLOR_LEMONCHIFFON                 (RH_MAKE_COLOR(255,250,205))  // 柠檬沙
#define RH_COLOR_PALEGOLDROD                  (RH_MAKE_COLOR(238,232,170))  // 灰秋
#define RH_COLOR_KHAKI                        (RH_MAKE_COLOR(240,230,140))  // 卡其布
#define RH_COLOR_GOLDEN                       (RH_MAKE_COLOR(255,215,  0))  // 金色
#define RH_COLOR_CORNMILK                     (RH_MAKE_COLOR(255,248,220))  // 玉米
#define RH_COLOR_GOLDROD                      (RH_MAKE_COLOR(218,165, 32))  // 秋天
#define RH_COLOR_DARKGOLDROD                  (RH_MAKE_COLOR(184,134, 11))  // 深秋
#define RH_COLOR_FLORALWHITE                  (RH_MAKE_COLOR(255,250,240))  // 白花
#define RH_COLOR_OLDLACE                      (RH_MAKE_COLOR(253,245,230))  // 浅米色
#define RH_COLOR_WHEAT                        (RH_MAKE_COLOR(245,222,179))  // 小麦
#define RH_COLOR_MOCCASIN                     (RH_MAKE_COLOR(255,228,181))  // 鹿皮
#define RH_COLOR_ORANGE                       (RH_MAKE_COLOR(255,165,  0))  // 橙色
#define RH_COLOR_PAPAYAWHIP                   (RH_MAKE_COLOR(255,239,213))  // 木瓜
#define RH_COLOR_BLANCHEDALMOND               (RH_MAKE_COLOR(255,235,205))  // 漂白的杏仁
#define RH_COLOR_NAVAJOWHITE                  (RH_MAKE_COLOR(255,222,173))  // 耐而节白
#define RH_COLOR_ANTIQUEWHITE                 (RH_MAKE_COLOR(250,235,215))  // 古白
#define RH_COLOR_TAN                          (RH_MAKE_COLOR(210,180,140))  // 晒
#define RH_COLOR_BURLYWOOD                    (RH_MAKE_COLOR(222,184,135))  // 树干
#define RH_COLOR_BISQUE                       (RH_MAKE_COLOR(255,228,196))  // 乳脂
#define RH_COLOR_DARKORANGE                   (RH_MAKE_COLOR(255,140,  0))  // 深橙色
#define RH_COLOR_LINEN                        (RH_MAKE_COLOR(255,240,230))  // 亚麻
#define RH_COLOR_PERU                         (RH_MAKE_COLOR(205,133, 63))  // 秘鲁
#define RH_COLOR_SANDYBROWN                   (RH_MAKE_COLOR(244,164, 96))  // 沙棕
#define RH_COLOR_CHOCOLATE                    (RH_MAKE_COLOR(210,105, 30))  // 巧克力
#define RH_COLOR_SEASHELL                     (RH_MAKE_COLOR(255,245,238))  // 海贝
#define RH_COLOR_SIENNA                       (RH_MAKE_COLOR(160, 82, 45))  // 土黄赭
#define RH_COLOR_SALMON                       (RH_MAKE_COLOR(255,160,122))  // 三文鱼
#define RH_COLOR_CORAL                        (RH_MAKE_COLOR(255,127, 80))  // 珊瑚红
#define RH_COLOR_ORANGERED                    (RH_MAKE_COLOR(255, 69,  0))  // 橙红
#define RH_COLOR_TOMATO                       (RH_MAKE_COLOR(255, 99, 71))  // 番茄
#define RH_COLOR_MISTYROSE                    (RH_MAKE_COLOR(255,228,225))  // 迷雾玫瑰
#define RH_COLOR_BLOODYMEAT                   (RH_MAKE_COLOR(250,128,114))  // 鲜肉
#define RH_COLOR_LIGHTCORAL                   (RH_MAKE_COLOR(240,128,128))  // 浅珊瑚红
#define RH_COLOR_ROSEBROWN                    (RH_MAKE_COLOR(188,143,143))  // 玫瑰棕
#define RH_COLOR_INDIANRED                    (RH_MAKE_COLOR(205, 92, 92))  // 浅粉红
#define RH_COLOR_BROWN                        (RH_MAKE_COLOR(165, 42, 42))  // 棕色
#define RH_COLOR_FIREBRICK                    (RH_MAKE_COLOR(178, 34, 34))  // 火砖
#define RH_COLOR_DARKRED                      (RH_MAKE_COLOR(139,  0,  0))  // 深红
#define RH_COLOR_MAROON                       (RH_MAKE_COLOR(128,  0,  0))  // 栗色
           
// Neutral Series
#define RH_COLOR_WHITESMOKE                   (RH_MAKE_COLOR(245,245,245))  // 烟白
#define RH_COLOR_GAINSBORO                    (RH_MAKE_COLOR(220,220,220))  // 赶死部落
#define RH_COLOR_LIGHTGRAY                    (RH_MAKE_COLOR(211,211,211))  // 浅灰
#define RH_COLOR_SILVER                       (RH_MAKE_COLOR(192,192,192))  // 银色
#define RH_COLOR_DARKGRAY                     (RH_MAKE_COLOR( 73, 73, 73))  // 深灰
#define RH_COLOR_DIMGRAY                      (RH_MAKE_COLOR( 54, 54, 54))  // 暗灰

#define RH_COLOR_COAL                         (RH_MAKE_COLOR( 34, 35, 34))  // 煤炭黑

#endif

