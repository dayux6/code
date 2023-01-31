#include <bits/stdc++.h>

const int bsiz = 5e4;

long long sum[] = {0, 788918560, 3155396535, 7099016595, 12619776756, 19719661649, 28396335215, 38655778784, 50480478389, 63888736843, 78878300214, 95442289071, 113586123418, 133313457557, 154612312331, 177479091895, 201930714399, 227959684542, 255569259452, 284757726400, 315518883845, 347865101326, 381782916267, 417261464052, 454347742086, 492997058997, 533232472824, 575037547606, 618409302632, 663380526379, 709921972600, 758038618622, 807742468628, 859011455806, 911860117601, 966301645500, 1022300316403, 1079886226145, 1139049459409, 1199773741427, 1262107057507, 1326015953402, 1391448482311, 1458500578713, 1527124944834, 1597307610884, 1669068889508, 1742448759837, 1817389633722, 1893910228977, 1971980908429, 2051641466395, 2132900183558, 2215712412007, 2300122122495, 2386077268685, 2473667550836, 2562794516781, 2653516140219, 2745831583773, 2839667910306, 2935124833635, 3032145911716, 3130773464473, 3230932923172, 3332715984365, 3436018861046, 3540903483143, 3647406552851, 3755467307690, 3865153559435, 3976288773460, 4089166792772, 4203548448983, 4319452612364, 4437000070445, 4556164412637, 4676831574984, 4799107835507, 4922975709121, 5048429679736, 5175419416421, 5303964680275, 5434085331669, 5565792320684, 5699091637414, 5834020891861, 5970460197771, 6108504228692, 6248135002190, 6389328710475, 6532060080723, 6676410108322, 6822333580958, 6969826900414, 7118947259623, 7269615163848, 7421836102112, 7575673383994, 7731065182911, 7888006418491, 8046560835579, 8206712360115, 8368352506149, 8531654517156, 8696509905696, 8862905875146, 9030995503516, 9200537823083, 9371697623663, 9544436388903, 9718778219983, 9894723232906, 10072181787466, 10251224180166, 10431824136562, 10614046062074, 10797839635417, 10983229660479, 11170177392522, 11358653942539, 11548783766141, 11740457476527, 11933701532019, 12128507492381, 12324929063955, 12522915589267, 12722566980213, 12923676036163, 13126439407993, 13330702043661, 13536636221291, 13744065599397, 13953100102330, 14163769084600, 14375941082196, 14589776377257, 14805144646303, 15021965709648, 15240552160806, 15460592174277, 15682214543117, 15905442127484, 16130187080811, 16356599093905, 16584493750845, 16814102578425, 17045206836895, 17277852284473, 17512117072495, 17747921030069, 17985361146414, 18224380329227, 18465018348332, 18707165850229, 18950912133502, 19196259116096, 19443196087348, 19691640282486, 19941566858567, 20193260551464, 20446521570785, 20701239226717, 20957592414723, 21215552784510, 21475084425599, 21736130625471, 21998850450840, 22263115053504, 22528858525326, 22796303862459, 23065262091997, 23335834000759, 23608058717798, 23881697341714, 24156965933230, 24433822044066, 24712297041196, 24992441551811, 25273947538341, 25557232476901, 25841941264867, 26128190360343, 26416110707468, 26705621044465, 26996730667779, 27289388413247, 27583707773417, 27879442226206, 28176826124668, 28475864329950, 28776311835992, 29078467340699, 29382073363829, 29687540482609, 29994346579760, 30302788732528, 30612719395822, 30924325660821, 31237562621343, 31552202992945, 31868527976184, 32186438606534, 32506006026135, 32826996770687, 33149602450554, 33473668979138, 33799485004075, 34126787172892, 34455654416423, 34786206605399, 35118279648300, 35451908622968, 35787240254509, 36123978935595, 36462366853743, 36802408665214, 37144038381314, 37487137961335, 37831965619930, 38178128490145, 38525897635490, 38875273112521, 39226280109891, 39578994584863, 39933093904956, 40288881145223, 40646312210682, 41005203716547, 41365538522822, 41727572980845, 42091189651984, 42456539675007, 42823302039404, 43191662609408, 43561626076275, 43933222804944, 44306293788411, 44680955272776, 45057306526892, 45434992773799, 45814451486122, 46195456171864, 46578073959053, 46962055161389, 47347859536266, 47735111450021, 48124058527351, 48514414791332, 48906474497998, 49300032288924, 49695250290063, 50091861262542, 50490308726536, 50890271882683, 51291705057059, 51694921102522, 52099682994700, 52505913430447, 52913800157463, 53323102563796, 53733947645858, 54146476161139, 54560576108695, 54976248606882, 55393573694095, 55812386360733, 56232841586252, 56654708598352, 57078398844795, 57503601706111, 57930384786269, 58358867336531, 58788733233377, 59220189436122, 59653078880902, 60087766585925, 60524101288798, 60961888862022, 61401105967066, 61841963195166, 62284507445916, 62728735620346, 63174591061128, 63621848924314, 64070529599330, 64520952097384, 64972907035372, 65426284135534, 65881478558164, 66338166416488, 66796487017524, 67256449582823, 67717896307208, 68180827772526, 68645484645851, 69111811203152, 69579326327309, 70048602448319, 70519455059531, 70991858139566, 71465971503575, 71941637046712, 72418749335650, 72897735980327, 73378192492236, 73859885466255, 74343649707901, 74828685113640, 75315278443286, 75803490085206, 76293339669462, 76784667694043, 77277725167381, 77772284076910, 78268401854440, 78766071159193, 79265441145692, 79766248238369, 80268789458243, 80772718565086, 81278528902077, 81785635912447, 82294427036948, 82804768853802, 83316762985578, 83830426762547, 84345482839233, 84862101244704, 85380429895651, 85900163732161, 86421731292334, 86944610915585, 87469143594981, 87995213313794, 88522868708777, 89052242125139, 89583038406090, 90115524292555, 90649479866726, 91185189856599, 91722142345966, 92260855642194, 92801052211065, 93342895340488, 93886788910677, 94431634183311, 94978301524778, 95526617348137, 96076462944796, 96627767181730, 97180668609321, 97735207943940, 98291412179861, 98848940758118, 99408311258732, 99969199229313, 100531547412535, 101095469558396, 101660972865699, 102228157538641, 102797064393438, 103367239491039, 103939065294642, 104512494907653, 105087710961954, 105664189919043, 106242348936601, 106822171000974, 107403579288243, 107986588803182, 108571253145456, 109157234507431, 109744915691450, 110334369871761, 110925192252702, 111517415215283, 112111446176921, 112707231155426, 113304228739215, 113902936771075, 114503257451930, 115105282171827, 115708506870970, 116313417710633, 116919858694794, 117528315046297, 118138067089233, 118749790427982, 119362436296691, 119976855815020, 120592995313671, 121210657298018, 121829997973946, 122450482783233, 123072834154212, 123697018761029, 124322671091910, 124949821639024, 125578563889313, 126208834750356, 126840818803995, 127474018707936, 128109187315686, 128745674981981, 129383664767039, 130023501709760, 130664720863435, 131307424375089, 131951822156966, 132597929735801, 133245326811862, 133894916463160, 134545607009415, 135197767143384, 135851698236441, 136507246082472, 137164446613801, 137823137628242, 138483323516049, 139145119797107, 139808438758268, 140473577520927, 141139869703984, 141808127491147, 142477601693242, 143149102315753, 143821953848215, 144496242699680, 145172081807246, 145850002026728, 146528928879305, 147209730823206, 147892022098614, 148575640634548, 149261331232273, 149948654168042, 150637031496960, 151327319549323, 152019114955535, 152712383684177, 153407181544804, 154103698506453, 154801830818000, 155501596598765, 156202856032885, 156905289700386, 157609904859794, 158315566562920, 159023350243095, 159732588518684, 160443150338129, 161155402051878, 161869306049943, 162584746145900, 163301729822887, 164020413530097, 164740628507348, 165462322271926, 166185490366134, 166910373245825, 167636807904703, 168364773453881, 169094441043038, 169825819571347, 170558585007836, 171293129200531, 172029116865432, 172766447191711, 173505596156115, 174246568191623, 174989103690965, 175732903608580, 176478101679186, 177225519026544, 177974322713295, 178724150887054, 179475634708793, 180229361979450, 180984061125911, 181740358007941, 182498283564929, 183257925043108, 184019055575781, 184782037273070, 185546326368964, 186312127002142, 187079371130160, 187848417362594, 188618988569252, 189391270711517, 190165379377068, 190940711869889, 191717685847416, 192496145056065, 193276188832180, 194057888978019, 194841113181850, 195626068347335, 196412409627794, 197200511462951, 197990328365517, 198781133434135, 199573861901119, 200368038716009, 201164232076167, 201961668092419, 202760842918791, 203561323833367, 204363540413465, 205167294584275, 205972751047987, 206779712052749, 207588115475499, 208398143425851, 209209852539035, 210023064228067, 210838101162293, 211654726994735, 212472632357679, 213292272351683, 214112974890581, 214935715751054, 215760086589242, 216585880143836, 217413279829462, 218242394963292, 219072868796470, 219904887385600, 220738737197631, 221574274574554, 222410898484007, 223249298556057, 224089532379473, 224931009729715, 225774209168501, 226619005419580, 227465507717127, 228313599354908, 229163286631364, 230014443237224, 230867218271907, 231721427259824, 232577488701677, 233434935518721, 234293749046999, 235154408097044, 236016749352250, 236880188793170, 237745486251224, 238612394623420, 239480947617319, 240351209708355, 241222586751405, 242095798907615, 242970565941616, 243846978590294, 244724713232620, 245604339853367, 246485642988643, 247368260832343, 248252286391574, 249137992316124, 250025419179304, 250914315973163, 251804939714806, 252697141903913, 253590900709248, 254486273052367, 255383113699360, 256281400025809, 257181333568222, 258083229882343, 258986326604036, 259891069816611, 260797550714644, 261705237305623, 262614581274760, 263525990455241, 264438711332164, 265352821473782, 266268577413530, 267186274368253, 268105011984011, 269025418709760, 269947318912506, 270870857806363, 271796268367031, 272723113501125, 273651672212086, 274581915052920, 275513606881143, 276446430541897, 277380814541943, 278317215837026, 279255365158725, 280194705314209, 281136032028455, 282078455989730, 283022810623903, 283968731943701, 284916255733999, 285864948524098, 286815588080131, 287767763859037, 288721104581749, 289676854158470, 290633407494980, 291592120106285, 292551822338696, 293513293962206, 294476203956562, 295440675629581, 296407242887634, 297375108362363, 298344645754032, 299315358197423, 300287921165440, 301262368327021, 302237812456943, 303215325854349, 304194061703398, 305174429064899, 306156606649517, 307140054542062, 308125224183859, 309112069561179, 310100231004963, 311090650893582, 312082032317531, 313075208202068, 314070346919031, 315066324285353, 316064312652545, 317063575344046, 318064874318853, 319067204334771, 320071106716402, 321077068392207, 322084286534530, 323092834533908, 324102812060664, 325114882777505, 326128363797768, 327143693821821, 328160700029852, 329179263766530, 330199031881135, 331220286329452, 332243751709912, 333268081496923, 334294530751485, 335322507715244, 336351820213435, 337382926848552, 338415557570475, 339449355362161, 340485318649996, 341522669719773, 342561609574026, 343601503987150, 344644076670727, 345687565046441, 346732647594292, 347779442666075, 348827999412072, 349877812950465, 350929205138188, 351982173440196, 353036976661811, 354093058712080, 355150893226135, 356210126259928, 357270863666049, 358333490411201, 359397649258774, 360463440891509, 361530556231223, 362599356551920, 363669825008515, 364742039911022, 365815801320034, 366890722435593, 367966966903854, 369045473859237, 370125101615408, 371206460120961, 372289473743524, 373374009012664, 374460052066377, 375547926942930, 376637330595767, 377728061351304, 378820349305785, 379914481075366, 381010335321801, 382108134535011, 383207042178266, 384306886756797, 385408889235844, 386512653758269, 387618102604842, 388724646552629, 389833006449384, 390942797975885, 392054306935761, 393167293623884, 394281498270361, 395397874141978, 396515904218171, 397634991365498, 398755819472593, 399878427483040, 401002690053940, 402128120749213, 403255199672933, 404383880849940, 405513935103229, 406645627833670, 407779050472007, 408914104545296, 410050635667337, 411189280020648, 412329025447147, 413470278865642, 414613155151231, 415757594222834, 416903709941482, 418051529492887, 419200806872450, 420351826397317, 421503874030845, 422658034036532, 423813482095987, 424970428942498, 426129326292527, 427289805201718, 428451560860225, 429615229420532, 430780123206653, 431946374307452, 433115395969083, 434284907929249, 435456426616043, 436629498557544, 437804357712143, 438980075354332, 440158022236397, 441337273717480, 442518117696479, 443700785128368, 444884466335377, 446069968052603, 447257319480788, 448445920306119, 449636285070950, 450828366561507, 452021244764484, 453216560538271, 454413143257774, 455611171307252, 456811243841725, 458012591351118, 459215594439647, 460420713934692, 461626903504215, 462833732104334, 464043144514190, 465254305625985, 466466384158994, 467680331058049, 468895935150198, 470113126140473, 471331870043098, 472551550612546, 473773754110201, 474997397689092, 476222351011511, 477448539471244, 478676731010253, 479906232817497, 481137628942924, 482370341677323, 483604723361756, 484840732219243, 486078502783426, 487317599516796, 488558542938123, 489800654812396, 491044626058265, 492290055215884, 493537568104004, 494786511566737, 496036780782212, 497288078687075, 498541310575306, 499796370875692, 501053124371609, 502311048434634, 503570932611793, 504832117648332, 506095267027298, 507359870327461, 508625537217824, 509893188647549, 511162342744392, 512433226199544, 513705149524417, 514979466511630, 516254721977073, 517531838094476, 518810153815486, 520090759224957, 521372492768116, 522655694421633, 523940629131405, 525227194894238, 526515110129201, 527804592375756, 529096162602710, 530389295405887, 531683645751590, 532979440288156, 534277354701932, 535577066434195, 536877200398980, 538179750242747, 539483587107263, 540789211984072, 542096689880589, 543405312977344, 544715647268056, 546027112014839, 547340453525274, 548655382442207, 549971845325285, 551289875588702, 552609377717985, 553930842870156, 555253935151583, 556578011372618, 557904043802843, 559231553525000, 560560797231062, 561891496412883, 563223842887396, 564557769727676, 565893918398767, 567230485175282, 568568797712519, 569908775603277, 571250387328252, 572594634091788, 573939260893978, 575285585031277, 576633667865708, 577983254186141, 579334388067763, 580687242347626, 582041517478733, 583398097965091, 584755270448372, 586114338052715, 587475044012816, 588836926465073, 590200984076782, 591566435434752, 592933246465625, 594301192260622, 595671705591071, 597043488679731, 598416868003318, 599792024456983, 601168210040202, 602546128132505, 603925412183064, 605307051270674, 606689522111225, 608073863217610, 609459637148362, 610847475951247, 612236307372980, 613626918195011, 615019351583820, 616413550646277, 617808904087659, 619205551427364, 620604685879335, 622004390168115, 623406459049262, 624809584881543, 626214568163994, 627620724078945, 629028958441443, 630438392638834, 631849316357075, 633261658438707, 634675938808934, 636092610653580, 637509698776262, 638929207947141, 640349200289948, 641771390933472, 643195250407981, 644620421080717, 646047457075557, 647476071528896, 648905326498030, 650337221742395, 651770989724154, 653205700485228, 654642117946977, 656080376576910, 657520113601153, 658961756654088, 660403808478278, 661848185602193, 663293912063598, 664740982760803, 666190065205226, 667640857595266, 669092641297411, 670546727900772, 672002057157676, 673458746710819, 674917549624388, 676377849294317, 677839479697296, 679302638826678, 680767065999983, 682233446454203, 683701530822007, 685171051598656, 686642282731962, 688114829465837, 689588850145099, 691065225310874, 692542092136811, 694021591462044, 695502751477285, 696984607712049, 698468191057900, 699954249003975, 701440344686458, 702929298651804, 704419548386739, 705910870841336, 707403920227850, 708899053172364, 710395314664692, 711893382174917, 713392831174029, 714894029200526, 716396418465454, 717900926243324, 719406894408759, 720914236344445, 722423429397766, 723934252681361, 725447055455428, 726960105589096, 728475523645359, 729992022978894, 731510549600272, 733030405682848, 734552208852756, 736075426236313, 737600608837019, 739127069348938, 740654581560691, 742183726180298, 743715271532264, 745246921107361, 746781702521471, 748317162589395, 749854531660410, 751392977885662, 752933463232527, 754475683930314, 756019583363601, 757564406145017, 759111334053266, 760659977693916, 762209073848168, 763760785978262, 765313621160647, 766868674826933, 768425204251785, 769983018162635, 771542350600386, 773104087882402, 774666838909949, 776231002337642, 777797133416059, 779364441466565, 780933399577582, 782504254625029, 784075904931516, 785649160636546, 787224646490181, 788801117340176};

long long calc(int x)
{
    if (x == 1)
        return 1;

    std::vector<std::pair<int, int>> vct;
    for (int i = 2; i * i <= x; ++i)
        if (x % i == 0)
        {
            int cnt = 0;
            while (x % i == 0)
            {
                ++cnt;
                x /= i;
            }
            vct.emplace_back(i, cnt);
        }
    if (x != 1)
        vct.emplace_back(x, 1);

    if (vct.size() == 1)
        return vct.back().first ^ vct.back().second;
    else
    {
        long long ret = 1;
        for (std::pair<int, int> pr : vct)
            ret *= (pr.first ^ pr.second);
        return ret;
    }
}

int main()
{
    freopen("B.in", "r", stdin);
    int n;
    std::cin >> n;
    long long res = sum[n / bsiz];
    for (int i = (n / bsiz) * bsiz + 1; i <= n; ++i)
        res += calc(i);
    std::cout << res << std::endl;
    return 0;
}