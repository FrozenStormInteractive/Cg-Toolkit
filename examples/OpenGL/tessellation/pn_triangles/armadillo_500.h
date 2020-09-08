#define NUM_ARMADILLO_VERTS 252
#define NUM_ARMADILLO_FACES 500

static float ArmadilloVerts[252][3] = {
{-0.443932,0.458021,-0.464931},
{-0.453851,0.402898,-0.469001},
{-0.077217,0.106283,0.264009},
{-0.483932,0.455446,-0.438596},
{-0.426357,0.50711,-0.463412},
{-0.0305882,0.397011,-0.453962},
{-0.410593,0.547568,-0.411418},
{0.0597563,0.392866,-0.411897},
{0.156833,-0.35243,0.0527052},
{-0.478829,0.501771,-0.333307},
{0.443004,0.545278,-0.3614},
{-0.498501,0.387542,-0.411037},
{0.389992,0.592515,-0.394879},
{0.270122,0.0166755,0.12361},
{-0.458252,0.484904,-0.279624},
{-0.00237523,0.436463,-0.350616},
{0.405565,0.548047,-0.287616},
{-0.0426473,-0.0148746,0.511158},
{-0.426368,0.391224,-0.349653},
{0.0911531,-0.354578,0.240708},
{-0.385671,0.487483,-0.317452},
{0.0086625,0.342593,-0.296908},
{0.0920846,0.563277,-0.281273},
{0.146609,-0.249753,0.28364},
{-0.0339155,0.352519,-0.294841},
{0.434214,0.443741,-0.287464},
{0.0631661,0.477956,-0.289792},
{-0.326026,-0.0553651,0.0672879},
{0.429253,0.577354,-0.279147},
{-0.164215,0.64215,-0.299701},
{-0.102802,0.636963,-0.244025},
{0.49942,0.488337,-0.319581},
{-0.0850077,0.579378,-0.2946},
{-0.215132,0.121256,0.104656},
{-0.07365,0.509181,-0.266939},
{0.482956,0.442892,-0.268167},
{-0.0880451,0.562911,-0.216806},
{0.37871,0.38412,-0.251981},
{-0.238035,0.457645,0.0879746},
{-0.0782762,0.414623,-0.284556},
{-0.41295,0.425546,-0.358052},
{0.481788,0.46158,-0.19364},
{0.0686997,0.529562,-0.224228},
{0.142028,0.628395,-0.254512},
{-0.0682151,0.158683,0.301274},
{-0.370121,0.336642,-0.229528},
{-0.235295,0.401979,0.201703},
{-0.485843,0.38485,-0.299411},
{-0.322936,0.348961,-0.17205},
{0.0804442,0.426975,-0.246059},
{-0.312946,0.438431,-0.204304},
{-0.147462,0.57662,-0.217746},
{-0.137585,0.636687,-0.223266},
{0.289792,-0.34621,0.0767616},
{0.0814222,0.60578,-0.234541},
{0.16591,0.62266,-0.209639},
{-0.120648,0.461133,-0.159335},
{0.0062154,-0.0210105,0.447679},
{0.196942,-0.0968073,0.186374},
{0.442053,0.547824,-0.192244},
{0.222117,-0.0111515,0.208436},
{0.0293113,0.373602,-0.182006},
{0.143194,-0.121368,0.0664284},
{-0.2245,-0.0843577,0.147726},
{0.269601,-0.137584,0.105005},
{-0.0450109,0.567412,-0.199309},
{0.309947,0.372212,-0.163802},
{0.37384,0.504401,-0.194614},
{0.330524,0.323324,-0.110318},
{-0.495554,0.384058,-0.171276},
{0.264918,-0.174106,0.19472},
{0.117998,0.463288,-0.142907},
{-0.100664,0.513314,-0.211439},
{-0.419912,0.336443,-0.175224},
{0.35613,0.372721,-0.179399},
{0.396467,0.515049,-0.163715},
{0.469149,0.396289,-0.215822},
{-0.389849,0.482615,-0.166994},
{-0.0773732,0.54908,-0.144828},
{0.102894,0.511679,-0.168578},
{0.183664,-0.311309,0.0375787},
{-0.0342628,0.370739,-0.150904},
{-0.0890884,0.299982,-0.158246},
{0.0990058,0.438059,-0.0951126},
{-0.0240715,0.0436986,0.32567},
{-0.0267868,0.0403404,0.111586},
{0.314551,0.444118,-0.118616},
{0.0511406,0.555864,-0.151806},
{-0.493702,0.456356,-0.188904},
{0.127804,-0.287234,0.174123},
{0.245397,-0.308521,0.0478443},
{-0.116822,0.375259,-0.114967},
{0.0590443,0.36982,-0.124688},
{0.126901,-0.18535,0.0657543},
{0.0658809,0.0128657,0.178973},
{-0.00744011,0.312279,-0.117466},
{-0.331203,-0.159014,0.165054},
{0.0161681,0.398503,0.380689},
{-0.0145375,0.255129,-0.0969864},
{0.12131,0.155103,0.229913},
{0.124098,0.322192,-0.126728},
{-0.454526,0.437456,-0.106761},
{0.0778095,0.222262,-0.100881},
{-0.302416,0.420847,-0.148067},
{0.0120099,0.120668,0.287842},
{0.408027,0.331558,-0.149738},
{0.204467,0.412906,0.17628},
{-0.137138,0.557801,0.164385},
{0.125794,-0.0876599,0.140274},
{0.167963,0.385286,-0.090132},
{-0.275293,-0.124756,0.2161},
{0.501499,0.420073,-0.102876},
{-0.262096,-0.27214,0.219303},
{-0.203936,0.358338,-0.0850525},
{0.380641,0.497429,-0.104001},
{0.0491557,0.244512,0.308605},
{-0.237916,0.357643,0.137491},
{-0.400545,0.346951,-0.103863},
{-0.0189105,0.577842,-0.0893036},
{0.16087,0.0943633,0.20536},
{-0.204355,0.317453,-0.0512503},
{-0.180711,0.149179,0.164865},
{-0.211902,0.28374,0.136261},
{0.455904,0.480174,-0.0851415},
{-0.296046,0.305311,-0.0519231},
{0.29668,0.398459,-0.0813183},
{-0.234781,-0.351584,0.2543},
{0.226972,-0.300547,0.208783},
{-0.215574,-0.277646,0.217731},
{0.195915,0.312751,-0.0316819},
{-0.0772628,0.294759,0.350854},
{0.0928579,-0.182485,0.132361},
{0.195564,0.359207,-0.0542186},
{0.473805,0.380565,-0.0629406},
{-0.0672999,0.586914,-0.069839},
{0.0942788,0.515027,-0.0640576},
{-0.141892,0.493184,-0.0587561},
{-0.338729,-0.344365,-0.00106416},
{0.0408466,0.224976,-0.0838304},
{-0.0539061,0.0536396,0.223428},
{-0.154155,0.258969,-0.0899157},
{-0.0282058,0.162462,-0.0642403},
{0.26583,0.294967,-0.00844776},
{-0.365987,0.432697,-0.0664879},
{-0.0776035,0.207296,-0.0591871},
{0.132328,-0.350405,0.314483},
{0.196697,0.422546,-0.0270428},
{-0.0126457,0.0828706,-0.0365162},
{0.273919,-0.309715,0.131681},
{-0.221026,0.420057,-0.0666556},
{-0.182301,-0.138734,0.1693},
{0.256001,-0.0893238,-0.0156109},
{0.194633,-0.260953,0.282358},
{-0.205069,0.480067,-0.0146016},
{0.180669,0.360553,0.271527},
{0.0450975,0.14271,-0.0272316},
{0.452937,0.438965,-0.032875},
{-0.262824,-0.352917,0.0471452},
{0.140697,0.206613,0.122876},
{-0.255436,0.0730061,0.214133},
{0.0852169,0.560702,-0.0640284},
{0.142032,0.538337,0.182638},
{0.229535,-0.137448,0.24059},
{0.285778,-0.35785,0.13833},
{0.135006,0.0894283,0.00790306},
{0.085481,0.275252,0.315792},
{-0.310811,-0.0384429,-0.0297537},
{-0.168685,-0.355058,0.217766},
{0.269683,-0.0808383,0.0720327},
{-0.169445,0.379738,0.311305},
{-0.152608,0.275324,0.280656},
{-0.0731415,0.473127,0.345707},
{-0.224737,0.443412,0.0312207},
{-0.178273,-0.0105803,0.236846},
{-0.112142,0.113184,-0.00187744},
{-0.109171,0.390497,0.356629},
{-0.365307,0.328111,-0.0162006},
{0.222632,0.436161,0.0249833},
{-0.0330531,-0.057927,0.530999},
{-0.185046,-0.292751,0.156308},
{0.190424,0.0162911,-0.0279871},
{0.209308,-0.269622,0.136132},
{-0.283824,-0.172659,0.0225684},
{0.210626,-0.169725,0.0263499},
{0.118183,-0.290245,0.257413},
{-0.17259,0.463368,0.270778},
{-0.317927,0.0226386,0.0945701},
{0.276913,0.377033,0.125913},
{-0.078541,0.0597584,0.0247099},
{0.225569,0.433415,0.120452},
{-0.045761,-0.0329526,0.400021},
{-0.000476687,0.0377043,0.199397},
{0.0360624,0.0575481,0.251586},
{0.0435369,0.563112,0.252166},
{0.185914,0.287607,0.146244},
{0.225376,0.33467,0.146529},
{-0.00582813,0.0364538,0.0245267},
{-0.0560737,0.553316,0.27484},
{0.0963016,0.205069,0.289546},
{0.337953,0.411164,7.44419e-005},
{-0.295004,-0.328663,-0.0250434},
{-0.352483,-0.305117,0.0198018},
{-0.217074,-0.122042,0.00904939},
{0.0813719,0.0400498,0.00258052},
{0.116041,0.17194,0.0486802},
{0.191189,0.289786,0.0437236},
{0.362761,0.326069,-0.0403373},
{0.318189,0.315944,0.0666147},
{-0.384579,-0.351928,0.112323},
{0.107737,-0.216596,0.231389},
{-0.216708,-0.0486461,-0.019031},
{-0.158562,-0.182307,0.0658611},
{0.105288,0.0257207,0.230499},
{-0.102798,-0.0182392,0.158543},
{-0.270744,0.0917079,0.0716496},
{-0.156008,0.223594,0.0548802},
{-0.297813,-0.0102114,0.162345},
{0.374058,0.385328,0.0121637},
{-0.335164,-0.112848,0.0185978},
{0.153019,0.47367,0.271524},
{0.199704,0.0511024,0.239636},
{0.172342,0.12429,0.0578499},
{0.019639,0.510844,0.336728},
{0.266507,-0.351633,-0.00525875},
{0.0147424,-0.0347794,0.363266},
{-0.197038,-0.0888191,0.0776552},
{0.0968293,0.394996,0.354237},
{-0.155188,0.236858,0.180042},
{0.128259,0.220194,0.0224862},
{0.152864,0.254237,0.211529},
{-0.114642,0.254735,0.278579},
{0.0215988,0.590515,-0.0581903},
{-0.261672,-0.283012,0.0717429},
{-0.107603,-0.00192396,0.0765797},
{-0.133997,0.17827,0.0343982},
{-0.049247,0.25817,0.317776},
{-0.0381995,0.602903,0.119929},
{-0.165269,0.0814139,-0.00279777},
{-0.295094,-0.075407,0.131425},
{-0.112073,0.551448,0.0179244},
{-0.400405,-0.345385,0.0376837},
{0.224314,0.101908,0.125459},
{0.15099,-0.139134,0.236433},
{-0.230984,0.30852,0.0826815},
{-0.316919,-0.272615,0.134396},
{0.260522,0.0374537,0.0494871},
{0.0616526,0.00973672,0.097616},
{-0.309361,0.370806,0.0888094},
{-0.340991,0.41922,0.0185242},
{0.186556,0.49012,0.169639},
{-0.130112,0.128041,0.244385},
{0.0725099,0.586591,0.10507}};

static float ArmadilloNormals[252][3] = {
{0.311986,-0.0345013,-0.94946},
{0.276681,-0.476035,-0.834768},
{-0.324706,-0.22424,0.918849},
{-0.757096,0.213865,-0.617306},
{-0.0635192,0.400458,-0.914111},
{-0.527739,-0.265262,-0.806925},
{0.50188,0.863877,0.0428149},
{0.789104,0.0903972,-0.607572},
{-0.441102,-0.786114,-0.432958},
{-0.885777,0.458385,0.0726797},
{0.0568285,-0.0852245,-0.99474},
{-0.774273,-0.573205,-0.268211},
{-0.866943,0.473885,-0.154414},
{0.942711,0.14606,0.299937},
{-0.44981,0.830093,0.32957},
{0.0796953,0.672306,-0.735971},
{-0.984558,0.128254,-0.119146},
{-0.411766,0.662842,0.625371},
{0.399861,-0.834346,-0.379444},
{-0.992944,-0.115882,0.025187},
{0.713666,0.694664,-0.0901267},
{0.277399,-0.95965,-0.0460592},
{-0.396874,0.0418506,-0.916918},
{-0.357418,0.0694768,0.931357},
{-0.612124,-0.785962,-0.0870005},
{-0.530885,-0.272379,-0.802478},
{0.529137,0.408107,-0.74395},
{-0.971983,0.117676,0.203475},
{0.0967999,0.973594,0.206745},
{-0.704506,0.183403,-0.685591},
{0.570998,0.819115,-0.0548845},
{0.9424,0.033104,-0.332845},
{0.333401,0.0487599,-0.941523},
{-0.539821,0.741599,-0.398276},
{-0.479607,0.314293,-0.819266},
{0.675967,-0.539926,-0.501546},
{-0.669837,-0.369055,-0.644296},
{-0.128572,-0.48277,-0.866258},
{-0.873121,0.479288,0.0891153},
{-0.928263,-0.0956872,-0.359405},
{0.86941,-0.19933,-0.452098},
{0.954901,0.224295,0.194563},
{0.387196,0.14176,-0.911034},
{0.613266,0.247679,-0.75004},
{-0.312213,-0.216263,0.925069},
{0.366837,-0.831284,-0.417608},
{-0.919639,0.0608406,0.388023},
{-0.833658,-0.539315,-0.118972},
{0.494891,-0.634702,-0.593495},
{0.934615,-0.190942,-0.300061},
{0.906154,0.18678,-0.379472},
{-0.942343,-0.3341,0.0191515},
{-0.18603,0.679634,0.70957},
{0.948741,-0.211141,-0.235179},
{-0.767689,0.622864,-0.150646},
{0.703263,0.543086,0.458779},
{-0.79755,0.105529,-0.59395},
{0.885863,-0.0056251,0.463913},
{0.312146,0.27617,0.909008},
{0.560373,0.593117,0.578096},
{0.57393,-0.213067,0.7907},
{0.640272,-0.764987,-0.0696257},
{-0.829487,-0.215579,-0.515244},
{0.474408,-0.0612265,0.878173},
{0.999947,0.00478637,-0.00912049},
{0.41909,0.876965,-0.235153},
{-0.848755,0.182435,-0.496318},
{-0.870768,0.418613,-0.257927},
{-0.310447,-0.759385,-0.571801},
{-0.84525,-0.405429,0.348108},
{0.970469,-0.0869503,0.225012},
{0.903655,-0.142994,-0.403683},
{-0.927629,0.0373958,-0.371625},
{-0.352431,-0.935307,0.0315181},
{-0.655739,0.517816,-0.54943},
{-0.261613,0.868127,0.421799},
{0.777638,-0.531867,-0.335255},
{0.143746,0.936251,0.320579},
{-0.743541,0.548949,0.381841},
{0.968526,0.192178,-0.158194},
{-0.23267,0.733275,-0.638883},
{-0.362361,-0.859331,-0.360896},
{-0.0546868,-0.186386,-0.980953},
{0.461032,-0.431915,-0.775177},
{-0.345831,0.533479,0.771881},
{0.0166581,-0.99534,-0.0949751},
{-0.850056,0.494271,-0.181939},
{0.176931,0.964717,0.194978},
{-0.832995,0.514297,0.204006},
{-0.869196,0.0730187,-0.489047},
{0.437417,0.81669,-0.37641},
{-0.199364,-0.0956896,-0.975242},
{0.335784,-0.252068,-0.907585},
{-0.629625,-0.193931,-0.752305},
{-0.488248,-0.787478,0.376154},
{0.0201258,-0.190596,-0.981462},
{-0.872611,0.108577,0.476195},
{0.071585,-0.0532512,0.996012},
{0.0653437,-0.318762,-0.94558},
{0.732547,-0.103911,0.672739},
{0.372826,-0.0737842,-0.924963},
{-0.547598,0.304485,0.779375},
{0.229683,-0.646682,-0.727357},
{0.657394,0.676009,-0.332934},
{0.190685,-0.158444,0.96878},
{0.350823,-0.90181,-0.252313},
{0.856074,0.0566708,0.513738},
{-0.629246,0.754436,0.186749},
{-0.951039,-0.0122893,0.308826},
{0.413944,-0.146425,-0.898449},
{-0.0945607,0.356341,0.929559},
{0.978533,0.0620197,0.196537},
{-0.482718,0.106423,0.869286},
{-0.12994,-0.0990206,-0.986565},
{-0.33549,0.804763,0.489697},
{0.297256,-0.174993,0.938625},
{-0.846712,-0.224571,0.482335},
{-0.561874,-0.717501,0.411691},
{-0.0366726,0.862438,-0.504833},
{0.54627,0.512321,0.662658},
{-0.215965,-0.809273,-0.546294},
{-0.869987,0.469373,0.151035},
{-0.797304,-0.559355,0.226778},
{0.542713,0.739804,0.397685},
{-0.136845,-0.974951,-0.175341},
{-0.64791,0.549022,-0.528003},
{-0.0625963,-0.469974,0.880458},
{0.888131,0.050504,0.456807},
{0.48392,0.19712,0.852622},
{0.384212,-0.672633,-0.632413},
{-0.27067,-0.328998,0.904709},
{-0.986529,-0.049813,-0.155815},
{0.20886,0.00361696,-0.977939},
{0.735421,-0.530209,0.421941},
{-0.443523,0.760399,-0.474427},
{0.753799,0.520652,-0.400884},
{-0.629546,0.540699,-0.557957},
{-0.248134,-0.686565,-0.683416},
{0.206713,-0.502347,-0.839594},
{-0.243225,-0.834134,0.495038},
{-0.67397,-0.530187,-0.514456},
{-0.191742,-0.258593,-0.946765},
{0.127098,-0.980145,-0.15219},
{-0.259282,0.797067,0.545396},
{-0.422858,-0.513616,-0.746586},
{0.0720848,-0.526164,0.847322},
{0.550909,0.512252,-0.658861},
{-0.00629233,-0.469817,-0.882741},
{0.712757,0.700592,0.0338917},
{-0.386203,0.576564,-0.720015},
{0.804281,0.268563,0.530101},
{0.627346,-0.162467,-0.761605},
{0.317248,0.024469,0.948027},
{-0.762305,0.539811,-0.357065},
{0.82739,-0.136864,0.544696},
{0.389136,-0.209719,-0.89699},
{0.413267,0.37193,0.831191},
{0.479467,-0.751791,-0.452683},
{0.991817,-0.125545,-0.0231716},
{-0.680682,0.360752,0.637596},
{0.531406,0.52951,-0.661231},
{0.658032,0.699531,0.278659},
{0.519626,0.481352,0.705896},
{0.79034,-0.491445,0.365848},
{0.295685,0.280861,-0.913065},
{0.368773,-0.350844,0.860764},
{-0.586596,0.123405,-0.800423},
{0.913712,-0.251393,0.319267},
{0.976685,-0.039081,0.211091},
{-0.709838,-0.106565,0.696257},
{-0.631223,-0.499661,0.593209},
{-0.300277,0.362446,0.882307},
{-0.539772,0.839808,-0.0580389},
{-0.0633907,-0.379113,0.923177},
{-0.29924,-0.119193,-0.946704},
{-0.394969,0.0861206,0.914649},
{-0.713845,-0.559481,0.421196},
{0.584145,0.741612,-0.329826},
{0.222763,-0.838244,0.497719},
{0.985864,-0.0369344,-0.163429},
{0.224978,0.274,-0.935045},
{0.665001,0.0189541,-0.746602},
{-0.325501,-0.302573,-0.895823},
{0.0160531,-0.433377,-0.90107},
{-0.863081,0.0561746,0.501933},
{-0.677417,0.41335,0.60848},
{-0.958814,0.264515,0.103476},
{0.526199,0.0884557,0.845748},
{0.112931,-0.602141,-0.790363},
{0.688568,0.529089,0.495923},
{-0.710064,-0.687966,-0.150039},
{-0.174145,-0.976288,-0.128587},
{0.559546,-0.413289,0.718402},
{0.28496,0.815093,0.504402},
{0.866895,-0.388125,0.312814},
{0.568114,-0.331769,0.753111},
{-0.0201319,-0.83295,-0.552982},
{-0.28156,0.737713,0.613599},
{0.549212,-0.112381,0.828092},
{-0.0740181,0.880218,0.468763},
{0.245838,0.0980094,-0.964343},
{-0.404993,0.666712,-0.625681},
{0.345487,-0.185303,-0.919946},
{-0.339867,-0.428152,-0.837363},
{0.72767,0.0597064,-0.683323},
{0.584956,-0.811028,-0.00773362},
{0.483105,-0.845618,0.227023},
{0.538853,-0.668304,0.512842},
{-0.682954,-0.599852,0.416834},
{-0.8429,0.179711,0.507172},
{0.517042,-0.272267,-0.811504},
{0.900459,-0.0514609,-0.431886},
{-0.069666,-0.294123,0.953225},
{0.613021,-0.75344,0.237769},
{-0.639465,0.712436,-0.288999},
{-0.883315,-0.37999,-0.274523},
{-0.771964,-0.101457,0.627518},
{0.625024,0.0887813,0.77554},
{-0.794753,-0.155569,-0.586656},
{0.697779,0.385562,0.603694},
{0.477448,0.273129,0.835131},
{0.632273,0.612633,-0.474249},
{0.172225,0.479122,0.860686},
{0.235612,0.119858,-0.964428},
{0.547534,-0.817744,-0.177486},
{0.975431,-0.159385,-0.152087},
{0.45755,0.0562906,0.8874},
{-0.930838,-0.326975,0.163179},
{0.714775,-0.630725,-0.302129},
{0.825429,-0.291152,0.483629},
{-0.691728,-0.293255,0.659935},
{0.191949,0.921288,-0.338208},
{0.320739,0.108343,-0.940951},
{0.648465,-0.63205,-0.424271},
{-0.730913,0.119778,-0.671877},
{-0.0820148,-0.320633,0.943646},
{-0.18833,0.975117,0.116953},
{-0.165492,0.293568,-0.941504},
{-0.608037,0.117738,0.78513},
{-0.649121,0.757789,-0.0663166},
{-0.922148,0.193763,-0.334813},
{0.699078,0.681451,0.2166},
{-0.295952,0.460042,0.837122},
{-0.655746,-0.742657,0.135859},
{-0.959607,0.275236,-0.0583125},
{0.856859,0.337029,-0.390132},
{-0.736193,-0.662606,-0.137743},
{-0.730521,0.0806106,0.678116},
{-0.719184,0.431498,0.544596},
{0.862388,0.479588,0.162117},
{-0.497419,0.0436585,0.866411},
{0.529873,0.848,-0.0114778}};

static int ArmadilloFaces[500][3] = {
{225,63,150},
{38,185,107},
{186,216,159},
{1,3,0},
{214,159,121},
{170,169,116},
{11,3,1},
{11,1,18},
{205,207,195},
{4,40,0},
{3,9,4},
{251,193,161},
{5,7,21},
{21,24,5},
{236,193,251},
{40,4,6},
{152,23,184},
{209,131,184},
{9,6,4},
{1,0,40},
{154,194,106},
{213,225,233},
{25,31,35},
{213,85,139},
{173,216,238},
{7,15,49},
{11,9,3},
{25,10,31},
{104,99,198},
{11,18,47},
{39,5,24},
{57,17,178},
{10,16,12},
{6,9,14},
{14,20,6},
{112,96,244},
{168,60,58},
{25,35,37},
{6,20,40},
{128,179,150},
{132,92,109},
{241,119,220},
{49,15,26},
{16,10,25},
{15,5,39},
{47,14,9},
{10,12,28},
{17,190,178},
{34,26,15},
{197,107,185},
{44,250,2},
{49,21,7},
{57,178,190},
{152,162,242},
{190,224,57},
{84,17,57},
{152,242,23},
{93,183,181},
{17,84,190},
{29,36,51},
{192,104,84},
{70,127,181},
{34,36,32},
{192,84,57},
{30,32,29},
{20,14,77},
{245,241,13},
{16,75,28},
{195,189,106},
{100,92,132},
{230,250,44},
{224,192,57},
{31,10,28},
{119,158,99},
{54,22,42},
{40,45,18},
{34,15,39},
{121,234,33},
{193,219,161},
{34,65,26},
{158,229,99},
{191,139,85},
{22,54,43},
{122,243,227},
{21,49,61},
{29,32,36},
{213,173,63},
{65,42,26},
{68,37,105},
{52,30,29},
{116,247,243},
{18,45,47},
{81,24,21},
{108,131,209},
{26,79,49},
{152,184,145},
{26,42,79},
{29,51,52},
{163,148,127},
{36,34,72},
{23,209,184},
{34,32,65},
{139,173,213},
{37,35,76},
{37,74,25},
{25,74,67},
{35,31,41},
{55,43,54},
{195,106,194},
{59,31,28},
{170,116,122},
{20,50,40},
{88,47,69},
{239,107,236},
{67,16,25},
{20,77,50},
{244,240,208},
{56,39,81},
{14,88,77},
{31,59,41},
{63,238,110},
{43,42,22},
{9,11,47},
{130,97,175},
{212,99,104},
{41,76,35},
{16,67,75},
{235,97,130},
{59,28,75},
{45,73,47},
{38,46,185},
{81,39,24},
{52,65,30},
{205,195,194},
{43,55,42},
{40,50,45},
{106,189,249},
{65,32,30},
{97,171,175},
{94,192,191},
{69,47,73},
{45,50,48},
{222,97,226},
{49,79,71},
{65,87,42},
{58,60,212},
{51,36,72},
{229,194,154},
{87,54,42},
{61,81,21},
{168,58,64},
{150,63,110},
{103,48,50},
{56,72,39},
{97,235,165},
{246,62,108},
{115,229,165},
{42,55,79},
{78,65,52},
{64,70,181},
{76,41,111},
{157,126,208},
{51,72,78},
{37,76,105},
{66,74,37},
{55,54,87},
{45,117,73},
{45,48,117},
{167,179,128},
{214,186,159},
{173,2,250},
{139,2,173},
{13,60,168},
{123,111,41},
{192,212,104},
{66,37,68},
{67,74,86},
{41,59,75},
{75,114,123},
{127,148,181},
{93,131,108},
{88,101,77},
{8,163,145},
{238,63,173},
{169,185,46},
{77,103,50},
{61,71,83},
{87,79,55},
{61,92,81},
{81,91,56},
{41,75,123},
{75,67,114},
{171,97,222},
{13,241,220},
{95,100,102},
{173,250,159},
{88,69,101},
{112,110,96},
{66,86,74},
{89,8,19},
{78,52,51},
{96,218,244},
{95,98,82},
{179,211,150},
{95,92,100},
{224,191,192},
{92,61,83},
{125,86,66},
{184,131,89},
{85,246,94},
{229,154,165},
{117,69,73},
{125,66,68},
{239,38,107},
{81,92,95},
{94,191,85},
{69,117,101},
{4,0,3},
{67,86,114},
{87,135,79},
{148,53,90},
{99,212,119},
{91,82,113},
{193,222,219},
{76,111,133},
{124,117,48},
{238,96,110},
{206,217,207},
{82,140,113},
{101,143,77},
{144,140,82},
{70,64,162},
{82,91,95},
{213,63,225},
{113,56,91},
{92,83,109},
{143,117,248},
{103,113,48},
{82,98,144},
{149,103,172},
{91,81,95},
{103,77,143},
{249,219,106},
{118,65,78},
{18,1,40},
{138,95,102},
{145,127,152},
{76,133,105},
{149,56,113},
{87,118,135},
{65,118,87},
{68,105,206},
{160,118,231},
{84,139,190},
{98,95,138},
{102,100,129},
{113,103,149},
{71,109,83},
{172,103,143},
{130,175,169},
{220,119,212},
{136,78,56},
{39,72,34},
{165,226,97},
{98,138,141},
{214,121,33},
{221,119,241},
{219,249,161},
{199,114,86},
{227,215,121},
{101,117,143},
{215,234,121},
{162,64,58},
{134,236,231},
{68,129,132},
{132,129,100},
{192,94,212},
{216,186,27},
{71,79,135},
{136,134,118},
{124,48,120},
{125,68,132},
{108,209,242},
{98,141,144},
{142,129,68},
{176,117,124},
{105,133,206},
{146,109,71},
{187,195,207},
{118,160,135},
{80,181,148},
{38,172,247},
{115,198,229},
{125,199,86},
{241,245,221},
{120,113,140},
{144,215,140},
{238,27,96},
{231,118,134},
{183,64,181},
{111,123,156},
{179,232,211},
{109,146,132},
{126,128,112},
{232,179,157},
{146,125,132},
{53,223,90},
{182,232,244},
{110,128,150},
{141,234,144},
{141,138,155},
{58,212,108},
{129,228,102},
{138,204,155},
{113,120,48},
{70,162,152},
{104,2,84},
{135,146,71},
{122,230,170},
{197,193,236},
{156,114,199},
{134,136,153},
{138,102,228},
{133,217,206},
{133,156,217},
{125,146,177},
{211,225,150},
{153,56,149},
{153,136,56},
{184,19,145},
{189,187,217},
{123,114,156},
{162,58,242},
{160,177,135},
{108,212,94},
{228,204,138},
{176,248,117},
{156,133,111},
{249,189,177},
{68,206,142},
{157,179,167},
{118,78,136},
{158,194,229},
{166,237,210},
{119,221,158},
{160,231,251},
{200,157,137},
{240,201,137},
{202,218,166},
{235,44,104},
{245,168,151},
{215,243,140},
{243,176,124},
{233,85,213},
{226,219,222},
{60,220,212},
{210,237,188},
{237,166,214},
{155,196,147},
{141,174,234},
{215,144,234},
{120,140,243},
{208,112,244},
{185,171,197},
{58,108,242},
{134,153,239},
{180,151,203},
{174,141,147},
{2,104,44},
{135,177,146},
{205,194,158},
{210,202,166},
{202,211,232},
{147,141,155},
{151,180,245},
{147,188,174},
{242,209,23},
{155,164,203},
{142,205,129},
{251,177,160},
{121,250,230},
{203,164,180},
{188,147,196},
{196,155,203},
{164,155,204},
{27,238,216},
{156,199,217},
{251,249,177},
{8,53,163},
{185,175,171},
{175,185,169},
{190,139,191},
{149,172,153},
{134,239,236},
{170,130,169},
{137,208,240},
{110,112,128},
{7,5,15},
{182,218,202},
{221,180,164},
{188,237,174},
{165,235,115},
{249,251,161},
{124,120,243},
{177,199,125},
{128,126,167},
{137,201,200},
{202,232,182},
{203,151,183},
{189,195,187},
{126,112,208},
{143,248,172},
{205,142,207},
{158,228,205},
{171,222,197},
{198,99,229},
{218,27,166},
{210,188,233},
{230,122,227},
{196,85,188},
{153,172,38},
{218,182,244},
{210,225,202},
{216,173,159},
{208,137,157},
{223,8,80},
{62,93,108},
{204,158,221},
{246,108,94},
{237,234,174},
{206,207,142},
{222,193,197},
{38,239,153},
{27,218,96},
{131,93,89},
{159,250,121},
{116,243,122},
{204,221,164},
{2,139,84},
{228,129,205},
{62,203,183},
{148,163,53},
{248,176,247},
{219,226,154},
{89,19,184},
{201,232,200},
{62,246,203},
{230,227,121},
{235,170,230},
{220,60,13},
{145,19,8},
{151,64,183},
{227,243,215},
{44,235,230},
{221,245,180},
{165,154,226},
{70,152,127},
{106,219,154},
{38,116,46},
{90,223,80},
{240,244,201},
{62,183,93},
{246,85,203},
{235,104,115},
{233,225,210},
{187,207,217},
{186,214,166},
{211,202,225},
{151,168,64},
{145,163,127},
{191,224,190},
{177,189,199},
{85,196,203},
{181,89,93},
{148,90,80},
{49,71,61},
{251,231,236},
{157,200,232},
{80,8,89},
{244,232,201},
{78,72,56},
{33,234,237},
{27,186,166},
{89,181,80},
{217,199,189},
{38,247,116},
{235,130,170},
{33,237,214},
{14,47,88},
{228,158,204},
{107,197,236},
{172,248,247},
{188,85,233},
{223,53,8},
{168,245,13},
{104,198,115},
{169,46,116},
{247,176,243},
{157,167,126},
{16,28,12}};
