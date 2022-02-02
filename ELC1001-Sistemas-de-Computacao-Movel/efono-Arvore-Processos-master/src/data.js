const text = [
    {
        "_id" : "substituicao_de_liquidas",
        "isDeleted" : false,
        "__v" : 0,
        "children" : [ 
            "sub_liquida_todas", 
            "sub_liquida_oc"
        ],
        "createdAt" : ("2021-01-25T21:48:59.064Z"),
        "description" : "Substituição de uma líquida por outra",
        "name" : "Substituição de líquidas",
        "updatedAt" : ("2021-05-14T13:41:17.725Z")
    },
    {
        "_id" : "sub_liquida_todas",
        "isDeleted" : false,
        "__v" : 0,
        "children" : [ 
            "sub_liquida_todas_l", 
            "sub_liquida_todas_ʎ", 
            "sub_liquida_todas_r", 
            "sub_liquida_todas_R"
        ],
        "createdAt" : ("2021-01-25T21:48:59.271Z"),
        "name" : "Líquida (todas)",
        "parent" : "substituicao_de_liquidas",
        "updatedAt" : ("2021-05-14T13:41:18.342Z")
    },
    {
        "_id" : "sub_liquida_todas_l",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.300Z"),
        "name" : "l",
        "parent" : "sub_liquida_todas",
        "updatedAt" : ("2021-05-14T13:41:18.461Z")
    },
    {
        "_id" : "sub_liquida_todas_ʎ",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.306Z"),
        "name" : "ʎ",
        "parent" : "sub_liquida_todas",
        "updatedAt" : ("2021-05-14T13:41:18.463Z")
    },
    {
        "_id" : "sub_liquida_todas_r",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.310Z"),
        "name" : "r",
        "parent" : "sub_liquida_todas",
        "updatedAt" : ("2021-05-14T13:41:18.543Z")
    },
    {
        "_id" : "sub_liquida_todas_R",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.315Z"),
        "name" : "R",
        "parent" : "sub_liquida_todas",
        "updatedAt" : ("2021-05-14T13:41:18.623Z")
    },
    {
        "_id" : "sub_liquida_oc",
        "isDeleted" : false,
        "__v" : 0,
        "children" : [ 
            "sub_liquida_oc_l", 
            "sub_liquida_oc_r"
        ],
        "createdAt" : ("2021-01-25T21:48:59.320Z"),
        "description" : "OC (onset complexo): encontro de duas consoantes no início da sílaba",
        "name" : "Líquida (OC)",
        "parent" : "substituicao_de_liquidas",
        "updatedAt" : ("2021-05-14T13:41:18.625Z")
    },
    {
        "_id" : "sub_liquida_oc_l",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.324Z"),
        "name" : "l",
        "parent" : "sub_liquida_oc",
        "updatedAt" : ("2021-05-14T13:41:18.710Z")
    },
    {
        "_id" : "sub_liquida_oc_r",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.329Z"),
        "name" : "r",
        "parent" : "sub_liquida_oc",
        "updatedAt" : ("2021-05-14T13:41:18.749Z")
    },
    {
        "_id" : "semivocalizacao_de_liquidas",
        "isDeleted" : false,
        "__v" : 0,
        "children" : [ 
            "semi_liquida_todas"
        ],
        "createdAt" : ("2021-01-25T21:48:59.333Z"),
        "description" : "Substituição de líquida por semivogal",
        "name" : "Semivocalização de líquida",
        "updatedAt" : ("2021-05-14T13:41:18.751Z")
    },
    {
        "_id" : "semi_liquida_todas",
        "isDeleted" : false,
        "__v" : 0,
        "children" : [ 
            "semi_liquida_todas_l", 
            "semi_liquida_todas_ʎ", 
            "semi_liquida_todas_r", 
            "semi_liquida_todas_R"
        ],
        "createdAt" : ("2021-01-25T21:48:59.346Z"),
        "name" : "Líquida (todas)",
        "parent" : "semivocalizacao_de_liquidas",
        "updatedAt" : ("2021-05-14T13:41:18.912Z")
    },
    {
        "_id" : "semi_liquida_todas_l",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.351Z"),
        "name" : "l",
        "parent" : "semi_liquida_todas",
        "updatedAt" : ("2021-05-14T13:41:18.991Z")
    },
    {
        "_id" : "semi_liquida_todas_ʎ",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.354Z"),
        "name" : "ʎ",
        "parent" : "semi_liquida_todas",
        "updatedAt" : ("2021-05-14T13:41:18.994Z")
    },
    {
        "_id" : "semi_liquida_todas_r",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.359Z"),
        "name" : "r",
        "parent" : "semi_liquida_todas",
        "updatedAt" : ("2021-05-14T13:41:19.035Z")
    },
    {
        "_id" : "semi_liquida_todas_R",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.363Z"),
        "name" : "R",
        "parent" : "semi_liquida_todas",
        "updatedAt" : ("2021-05-14T13:41:19.119Z")
    },
    {
        "_id" : "dessonorizacao",
        "isDeleted" : false,
        "__v" : 0,
        "children" : [ 
            "des_plosiva", 
            "des_fricativa"
        ],
        "createdAt" : ("2021-01-25T21:48:59.367Z"),
        "name" : "Dessonorização",
        "updatedAt" : ("2021-05-14T13:41:19.159Z")
    },
    {
        "_id" : "des_plosiva",
        "isDeleted" : false,
        "__v" : 0,
        "children" : [ 
            "des_plosiva_b", 
            "des_plosiva_d", 
            "des_plosiva_g"
        ],
        "createdAt" : ("2021-01-25T21:48:59.372Z"),
        "name" : "Plosiva",
        "parent" : "dessonorizacao",
        "updatedAt" : ("2021-05-14T13:41:19.199Z")
    },
    {
        "_id" : "des_plosiva_b",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.376Z"),
        "name" : "b",
        "parent" : "des_plosiva",
        "updatedAt" : ("2021-05-14T13:41:19.201Z")
    },
    {
        "_id" : "des_plosiva_d",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.379Z"),
        "name" : "d",
        "parent" : "des_plosiva",
        "updatedAt" : ("2021-05-14T13:41:19.282Z")
    },
    {
        "_id" : "des_plosiva_g",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.383Z"),
        "name" : "g",
        "parent" : "des_plosiva",
        "updatedAt" : ("2021-05-14T13:41:19.361Z")
    },
    {
        "_id" : "des_fricativa",
        "isDeleted" : false,
        "__v" : 0,
        "children" : [ 
            "des_fricativa_v", 
            "des_fricativa_z", 
            "des_fricativa_ʒ"
        ],
        "createdAt" : ("2021-01-25T21:48:59.387Z"),
        "name" : "Fricativa",
        "parent" : "dessonorizacao",
        "updatedAt" : ("2021-05-14T13:41:19.363Z")
    },
    {
        "_id" : "des_fricativa_v",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.391Z"),
        "name" : "v",
        "parent" : "des_fricativa",
        "updatedAt" : ("2021-05-14T13:41:19.446Z")
    },
    {
        "_id" : "des_fricativa_z",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.395Z"),
        "name" : "z",
        "parent" : "des_fricativa",
        "updatedAt" : ("2021-05-14T13:41:19.448Z")
    },
    {
        "_id" : "des_fricativa_ʒ",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.399Z"),
        "name" : "ʒ",
        "parent" : "des_fricativa",
        "updatedAt" : ("2021-05-14T13:41:19.528Z")
    },
    {
        "_id" : "sonorizacao",
        "isDeleted" : false,
        "__v" : 0,
        "children" : [ 
            "son_plosiva", 
            "son_fricativa"
        ],
        "createdAt" : ("2021-01-25T21:48:59.403Z"),
        "name" : "Sonorização",
        "updatedAt" : ("2021-05-14T13:41:19.647Z")
    },
    {
        "_id" : "son_plosiva",
        "isDeleted" : false,
        "__v" : 0,
        "children" : [ 
            "son_plosiva_p", 
            "son_plosiva_t", 
            "son_plosiva_k"
        ],
        "createdAt" : ("2021-01-25T21:48:59.407Z"),
        "name" : "Plosiva",
        "parent" : "sonorizacao",
        "updatedAt" : ("2021-05-14T13:41:19.650Z")
    },
    {
        "_id" : "son_plosiva_p",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.411Z"),
        "name" : "p",
        "parent" : "son_plosiva",
        "updatedAt" : ("2021-05-14T13:41:19.729Z")
    },
    {
        "_id" : "son_plosiva_t",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.415Z"),
        "name" : "t",
        "parent" : "son_plosiva",
        "updatedAt" : ("2021-05-14T13:41:19.731Z")
    },
    {
        "_id" : "son_plosiva_k",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.419Z"),
        "name" : "k",
        "parent" : "son_plosiva",
        "updatedAt" : ("2021-05-14T13:41:19.811Z")
    },
    {
        "_id" : "son_fricativa",
        "isDeleted" : false,
        "__v" : 0,
        "children" : [ 
            "son_fricativa_f", 
            "son_fricativa_s", 
            "son_fricativa_ʃ"
        ],
        "createdAt" : ("2021-01-25T21:48:59.423Z"),
        "name" : "Fricativa",
        "parent" : "sonorizacao",
        "updatedAt" : ("2021-05-14T13:41:19.813Z")
    },
    {
        "_id" : "son_fricativa_f",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.427Z"),
        "name" : "f",
        "parent" : "son_fricativa",
        "updatedAt" : ("2021-05-14T13:41:19.896Z")
    },
    {
        "_id" : "son_fricativa_s",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.431Z"),
        "name" : "s",
        "parent" : "son_fricativa",
        "updatedAt" : ("2021-05-14T13:41:19.898Z")
    },
    {
        "_id" : "son_fricativa_ʃ",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.435Z"),
        "name" : "ʃ",
        "parent" : "son_fricativa",
        "updatedAt" : ("2021-05-14T13:41:19.978Z")
    },
    {
        "_id" : "anteriorizacao",
        "isDeleted" : false,
        "__v" : 0,
        "children" : [ 
            "ant_plosiva", 
            "ant_fricativa"
        ],
        "createdAt" : ("2021-01-25T21:48:59.439Z"),
        "name" : "Anteriorização",
        "updatedAt" : ("2021-05-14T13:41:20.019Z")
    },
    {
        "_id" : "ant_plosiva",
        "isDeleted" : false,
        "__v" : 0,
        "children" : [ 
            "ant_plosiva_k", 
            "ant_plosiva_g"
        ],
        "createdAt" : ("2021-01-25T21:48:59.443Z"),
        "name" : "Plosiva",
        "parent" : "anteriorizacao",
        "updatedAt" : ("2021-05-14T13:41:20.099Z")
    },
    {
        "_id" : "ant_plosiva_k",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.447Z"),
        "name" : "k",
        "parent" : "ant_plosiva",
        "updatedAt" : ("2021-05-14T13:41:20.101Z")
    },
    {
        "_id" : "ant_plosiva_g",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.451Z"),
        "name" : "g",
        "parent" : "ant_plosiva",
        "updatedAt" : ("2021-05-14T13:41:20.181Z")
    },
    {
        "_id" : "ant_fricativa",
        "isDeleted" : false,
        "__v" : 0,
        "children" : [ 
            "ant_fricativa_ʃ", 
            "ant_fricativa_ʒ"
        ],
        "createdAt" : ("2021-01-25T21:48:59.455Z"),
        "name" : "Fricativa",
        "parent" : "anteriorizacao",
        "updatedAt" : ("2021-05-14T13:41:20.264Z")
    },
    {
        "_id" : "ant_fricativa_ʃ",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.459Z"),
        "name" : "ʃ",
        "parent" : "ant_fricativa",
        "updatedAt" : ("2021-05-14T13:41:20.266Z")
    },
    {
        "_id" : "ant_fricativa_ʒ",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.462Z"),
        "name" : "ʒ",
        "parent" : "ant_fricativa",
        "updatedAt" : ("2021-05-14T13:41:20.346Z")
    },
    {
        "_id" : "posteriorizacao",
        "isDeleted" : false,
        "__v" : 0,
        "children" : [ 
            "post_plosiva", 
            "post_fricativa"
        ],
        "createdAt" : ("2021-01-25T21:48:59.466Z"),
        "name" : "Posteriorização",
        "updatedAt" : ("2021-05-14T13:41:20.348Z")
    },
    {
        "_id" : "post_plosiva",
        "isDeleted" : false,
        "__v" : 0,
        "children" : [ 
            "post_plosiva_p", 
            "post_plosiva_b", 
            "post_plosiva_t", 
            "post_plosiva_d"
        ],
        "createdAt" : ("2021-01-25T21:48:59.472Z"),
        "name" : "Plosiva",
        "parent" : "posteriorizacao",
        "updatedAt" : ("2021-05-14T13:41:20.427Z")
    },
    {
        "_id" : "post_plosiva_p",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.476Z"),
        "name" : "p",
        "parent" : "post_plosiva",
        "updatedAt" : ("2021-05-14T13:41:20.429Z")
    },
    {
        "_id" : "post_plosiva_b",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.480Z"),
        "name" : "b",
        "parent" : "post_plosiva",
        "updatedAt" : ("2021-05-14T13:41:20.509Z")
    },
    {
        "_id" : "post_plosiva_t",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.484Z"),
        "name" : "t",
        "parent" : "post_plosiva",
        "updatedAt" : ("2021-05-14T13:41:20.510Z")
    },
    {
        "_id" : "post_plosiva_d",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.488Z"),
        "name" : "d",
        "parent" : "post_plosiva",
        "updatedAt" : ("2021-05-14T13:41:20.590Z")
    },
    {
        "_id" : "post_fricativa",
        "isDeleted" : false,
        "__v" : 0,
        "children" : [ 
            "post_fricativa_s", 
            "post_fricativa_z", 
            "post_fricativa_f", 
            "post_fricativa_v"
        ],
        "createdAt" : ("2021-01-25T21:48:59.492Z"),
        "name" : "Fricativa",
        "parent" : "posteriorizacao",
        "updatedAt" : ("2021-05-14T13:41:20.669Z")
    },
    {
        "_id" : "post_fricativa_s",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.496Z"),
        "name" : "s",
        "parent" : "post_fricativa",
        "updatedAt" : ("2021-05-14T13:41:20.672Z")
    },
    {
        "_id" : "post_fricativa_z",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.500Z"),
        "name" : "z",
        "parent" : "post_fricativa",
        "updatedAt" : ("2021-05-14T13:41:20.755Z")
    },
    {
        "_id" : "post_fricativa_f",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.504Z"),
        "name" : "f",
        "parent" : "post_fricativa",
        "updatedAt" : ("2021-05-14T13:41:20.757Z")
    },
    {
        "_id" : "post_fricativa_v",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.508Z"),
        "name" : "v",
        "parent" : "post_fricativa",
        "updatedAt" : ("2021-05-14T13:41:20.836Z")
    },
    {
        "_id" : "plosivizacao",
        "isDeleted" : false,
        "__v" : 0,
        "children" : [ 
            "plos_fricativa", 
            "plos_liquida"
        ],
        "createdAt" : ("2021-01-25T21:48:59.511Z"),
        "name" : "Plosivização",
        "updatedAt" : ("2021-05-14T13:41:20.838Z")
    },
    {
        "_id" : "plos_fricativa",
        "isDeleted" : false,
        "__v" : 0,
        "children" : [ 
            "plos_fricativa_f", 
            "plos_fricativa_v", 
            "plos_fricativa_s", 
            "plos_fricativa_z", 
            "plos_fricativa_ʃ", 
            "plos_fricativa_ʒ"
        ],
        "createdAt" : ("2021-01-25T21:48:59.515Z"),
        "name" : "Fricativa (todas)",
        "parent" : "plosivizacao",
        "updatedAt" : ("2021-05-14T13:41:20.918Z")
    },
    {
        "_id" : "plos_fricativa_f",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.520Z"),
        "name" : "f",
        "parent" : "plos_fricativa",
        "updatedAt" : ("2021-05-14T13:41:20.957Z")
    },
    {
        "_id" : "plos_fricativa_v",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.523Z"),
        "name" : "v",
        "parent" : "plos_fricativa",
        "updatedAt" : ("2021-05-14T13:41:20.959Z")
    },
    {
        "_id" : "plos_fricativa_s",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.528Z"),
        "name" : "s",
        "parent" : "plos_fricativa",
        "updatedAt" : ("2021-05-14T13:41:20.960Z")
    },
    {
        "_id" : "plos_fricativa_z",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.531Z"),
        "name" : "z",
        "parent" : "plos_fricativa",
        "updatedAt" : ("2021-05-14T13:41:21.084Z")
    },
    {
        "_id" : "plos_fricativa_ʃ",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.535Z"),
        "name" : "ʃ",
        "parent" : "plos_fricativa",
        "updatedAt" : ("2021-05-14T13:41:21.086Z")
    },
    {
        "_id" : "plos_fricativa_ʒ",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.539Z"),
        "name" : "ʒ",
        "parent" : "plos_fricativa",
        "updatedAt" : ("2021-05-14T13:41:21.166Z")
    },
    {
        "_id" : "plos_liquida",
        "isDeleted" : false,
        "__v" : 0,
        "children" : [ 
            "plos_liquida_l", 
            "plos_liquida_r", 
            "plos_liquida_R", 
            "plos_liquida_ʎ"
        ],
        "createdAt" : ("2021-01-25T21:48:59.542Z"),
        "name" : "Líquida (todas)",
        "parent" : "plosivizacao",
        "updatedAt" : ("2021-05-14T13:41:21.245Z")
    },
    {
        "_id" : "plos_liquida_l",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.546Z"),
        "name" : "l",
        "parent" : "plos_liquida",
        "updatedAt" : ("2021-05-14T13:41:21.327Z")
    },
    {
        "_id" : "plos_liquida_r",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.550Z"),
        "name" : "r",
        "parent" : "plos_liquida",
        "updatedAt" : ("2021-05-14T13:41:21.329Z")
    },
    {
        "_id" : "plos_liquida_R",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.554Z"),
        "name" : "R",
        "parent" : "plos_liquida",
        "updatedAt" : ("2021-05-14T13:41:21.408Z")
    },
    {
        "_id" : "plos_liquida_ʎ",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.557Z"),
        "name" : "ʎ",
        "parent" : "plos_liquida",
        "updatedAt" : ("2021-05-14T13:41:21.410Z")
    },
    {
        "_id" : "reducao_do_ec",
        "isDeleted" : false,
        "__v" : 0,
        "children" : [ 
            "apagamento_ec"
        ],
        "createdAt" : ("2021-01-25T21:48:59.561Z"),
        "name" : "Redução do EC",
        "updatedAt" : ("2021-05-14T13:41:21.449Z")
    },
    {
        "_id" : "apagamento_ec",
        "isDeleted" : false,
        "__v" : 0,
        "children" : [ 
            "apagamento_ec_l", 
            "apagamento_ec_r"
        ],
        "createdAt" : ("2021-01-25T21:48:59.565Z"),
        "name" : "Apagamento do l ou r do EC",
        "parent" : "reducao_do_ec",
        "updatedAt" : ("2021-05-14T13:41:21.450Z")
    },
    {
        "_id" : "apagamento_ec_l",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.569Z"),
        "name" : "l",
        "parent" : "apagamento_ec",
        "updatedAt" : ("2021-05-14T13:41:21.534Z")
    },
    {
        "_id" : "apagamento_ec_r",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.573Z"),
        "name" : "r",
        "parent" : "apagamento_ec",
        "updatedAt" : ("2021-05-14T13:41:21.614Z")
    },
    {
        "_id" : "apagamento_fricativa_final",
        "isDeleted" : false,
        "__v" : 0,
        "children" : [ 
            "apag_fric_fin_cm_cf"
        ],
        "createdAt" : ("2021-01-25T21:48:59.577Z"),
        "name" : "Apagamento de fricativa final",
        "updatedAt" : ("2021-05-14T13:41:21.616Z")
    },
    {
        "_id" : "apag_fric_fin_cm_cf",
        "isDeleted" : false,
        "__v" : 0,
        "children" : [ 
            "apag_fric_fin_cm_cf_s"
        ],
        "createdAt" : ("2021-01-25T21:48:59.581Z"),
        "name" : "Fricativa (s) em CM e CF",
        "parent" : "apagamento_fricativa_final",
        "updatedAt" : ("2021-05-14T13:41:21.695Z")
    },
    {
        "_id" : "apag_fric_fin_cm_cf_s",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.584Z"),
        "name" : "s",
        "parent" : "apag_fric_fin_cm_cf",
        "updatedAt" : ("2021-05-14T13:41:21.697Z")
    },
    {
        "_id" : "apagamento_liquida_final",
        "isDeleted" : false,
        "__v" : 0,
        "children" : [ 
            "apag_liq_fin_cm_cf"
        ],
        "createdAt" : ("2021-01-25T21:48:59.589Z"),
        "name" : "Apagamento de líquida final",
        "updatedAt" : ("2021-05-14T13:41:21.777Z")
    },
    {
        "_id" : "apag_liq_fin_cm_cf",
        "isDeleted" : false,
        "__v" : 0,
        "children" : [ 
            "apag_liq_fin_cm_cf_r", 
            "apag_liq_fin_cm_cf_l"
        ],
        "createdAt" : ("2021-01-25T21:48:59.593Z"),
        "name" : "Líquida (r, l) em CM e CF",
        "parent" : "apagamento_liquida_final",
        "updatedAt" : ("2021-05-14T13:41:21.779Z")
    },
    {
        "_id" : "apag_liq_fin_cm_cf_r",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.600Z"),
        "name" : "r",
        "parent" : "apag_liq_fin_cm_cf",
        "updatedAt" : ("2021-05-14T13:41:21.858Z")
    },
    {
        "_id" : "apag_liq_fin_cm_cf_l",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.604Z"),
        "name" : "l",
        "parent" : "apag_liq_fin_cm_cf",
        "updatedAt" : ("2021-05-14T13:41:21.860Z")
    },
    {
        "_id" : "apagamento_liquida_intervocalica",
        "isDeleted" : false,
        "__v" : 0,
        "children" : [ 
            "apag_liq_inter_om"
        ],
        "createdAt" : ("2021-01-25T21:48:59.607Z"),
        "name" : "Apagamento de líquida intervocálica",
        "updatedAt" : ("2021-05-14T13:41:21.944Z")
    },
    {
        "_id" : "apag_liq_inter_om",
        "isDeleted" : false,
        "__v" : 0,
        "children" : [ 
            "apag_liq_inter_om_r", 
            "apag_liq_inter_om_l", 
            "apag_liq_inter_om_ʎ", 
            "apag_liq_inter_om_R"
        ],
        "createdAt" : ("2021-01-25T21:48:59.612Z"),
        "name" : "Líquida em OM",
        "parent" : "apagamento_liquida_intervocalica",
        "updatedAt" : ("2021-05-14T13:41:22.025Z")
    },
    {
        "_id" : "apag_liq_inter_om_r",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.615Z"),
        "name" : "r",
        "parent" : "apag_liq_inter_om",
        "updatedAt" : ("2021-05-14T13:41:22.105Z")
    },
    {
        "_id" : "apag_liq_inter_om_l",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.620Z"),
        "name" : "l",
        "parent" : "apag_liq_inter_om",
        "updatedAt" : ("2021-05-14T13:41:22.107Z")
    },
    {
        "_id" : "apag_liq_inter_om_ʎ",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.623Z"),
        "name" : "ʎ",
        "parent" : "apag_liq_inter_om",
        "updatedAt" : ("2021-05-14T13:41:22.187Z")
    },
    {
        "_id" : "apag_liq_inter_om_R",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.627Z"),
        "name" : "R",
        "parent" : "apag_liq_inter_om",
        "updatedAt" : ("2021-05-14T13:41:22.188Z")
    },
    {
        "_id" : "apagamento_liquida_inicial",
        "isDeleted" : false,
        "__v" : 0,
        "children" : [ 
            "apag_liq_ini_oi"
        ],
        "createdAt" : ("2021-01-25T21:48:59.631Z"),
        "name" : "Apagamento de líquida inicial",
        "updatedAt" : ("2021-05-14T13:41:22.268Z")
    },
    {
        "_id" : "apag_liq_ini_oi",
        "isDeleted" : false,
        "__v" : 0,
        "children" : [ 
            "apag_liq_ini_oi_l", 
            "apag_liq_ini_oi_R"
        ],
        "createdAt" : ("2021-01-25T21:48:59.635Z"),
        "name" : "Líquida em OI",
        "parent" : "apagamento_liquida_inicial",
        "updatedAt" : ("2021-05-14T13:41:22.347Z")
    },
    {
        "_id" : "apag_liq_ini_oi_l",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.639Z"),
        "name" : "l",
        "parent" : "apag_liq_ini_oi",
        "updatedAt" : ("2021-05-14T13:41:22.350Z")
    },
    {
        "_id" : "apag_liq_ini_oi_R",
        "isDeleted" : false,
        "__v" : 0,
        "createdAt" : ("2021-01-25T21:48:59.643Z"),
        "name" : "R",
        "parent" : "apag_liq_ini_oi",
        "updatedAt" : ("2021-05-14T13:41:22.429Z")
    },
    {
        "_id" : "metatese",
        "isDeleted" : false,
        "__v" : 0,
        "children" : [ 
            "metatese_ec"
        ],
        "createdAt" : ("2021-01-25T21:48:59.646Z"),
        "name" : "Metátese",
        "updatedAt" : ("2021-05-14T13:41:22.431Z")
    },
    {
        "_id" : "metatese_ec",
        "isDeleted" : false,
        "__v" : 0,
        "children" : [ 
            "metatese_ec"
        ],
        "createdAt" : ("2021-01-25T21:48:59.651Z"),
        "name" : " ",
        "parent" : "metatese_ec",
        "updatedAt" : ("2021-05-14T13:41:22.516Z")
    },
    {
        "_id" : "epentese",
        "isDeleted" : false,
        "__v" : 0,
        "children" : [ 
            "epentese_ec"
        ],
        "createdAt" : ("2021-01-25T21:48:59.658Z"),
        "name" : "Epêntese",
        "updatedAt" : ("2021-05-14T13:41:22.596Z")
    },
    {
        "_id" : "epentese_ec",
        "isDeleted" : false,
        "__v" : 0,
        "children" : [ 
            "epentese_ec"
        ],
        "createdAt" : ("2021-01-25T21:48:59.662Z"),
        "name" : " ",
        "parent" : "epentese_ec",
        "updatedAt" : ("2021-05-14T13:41:22.718Z")
    }
];

export default text;