// console.log("teste");

// baseServerUrl = "http://192.168.211.60:5500"
baseServerUrl = "http://192.168.1.83:5500"

var LOADER_API_tagsToLoad = 
[
    {
        whereToAppend: document.head,
        waitLoadOrError: false,
        tags: [
            {
                tagType: "meta",
                props: {
                    charset: "UTF-8",
                },
            },
            {
                tagType: "meta",
                props: {
                    "http-equiv": "X-UA-Compatible",
                    content: "IE=edge",
                },
            },
            {
                tagType: "meta",
                props: {
                    name: "viewport",
                    content: "width=device-width, initial-scale=1.0",
                },
            },
            {
                tagType: "title",
                content: "Irrigação 3.0"
            }
        ],
        // onFinish: ()=>{
        //     console.log("Finished meta tags");
        // }
    },
    {
        whereToAppend: document.head,
        tags: [
            {
                tagType: "script",
                props: {
                    src: "https://code.jquery.com/jquery-3.6.0.min.js",
                },
            },
            {
                tagType: "script",
                props: {
                    src: "https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js",
                    integrity: "sha384-ka7Sk0Gln4gmtz2MlQnikT1wXgYsOg+OMhuP+IlRH9sENBO0LRn5q+8nbTov4+1p",
                    crossorigin: "anonymous",
                },
            },
            {
                tagType: "script",
                props: {
                    src: `${baseServerUrl}/html_ctrl_panel/main.js`,
                    // src: "https://arturzahn.github.io/irrigacao-3.0/html_ctrl_panel/main.js",
                },
            }
        ],
        // onFinish: ()=>{
        //     console.log("Finished scripts");
        // }
    },
    {
        whereToAppend: document.head,
        tags: [
            // {
            //     tagType: "link",
            //     props: {
            //         href: `${baseServerUrl}/html_ctrl_panel/logo.ico`,
            //         rel: "icon",
            //         type: "image/x-icon"
            //     },
            // },
            {
                tagType: "link",
                props: {
                    href: "https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css",
                    rel: "stylesheet",
                    integrity: "sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3",
                    crossorigin: "anonymous",
                },
            },
            {
                tagType: "link",
                props: {
                    href: `${baseServerUrl}/html_ctrl_panel/main.css`,
                    // href: "https://arturzahn.github.io/irrigacao-3.0/html_ctrl_panel/main.css",
                    rel: "stylesheet",
                },
            },
        ],
        // onFinish: ()=>{
        //     console.log("Finished styles");
        // }
    },
]

var LOADER_API_contentLoaded = ()=>{
    // console.log("Content loaded");
    startApp(espAddress);
}

var loadApiScript = document.createElement("script");
loadApiScript.setAttribute("src", `${baseServerUrl}/html_ctrl_panel/loader.api.js`);
// loadApiScript.setAttribute("src", "https://arturzahn.github.io/irrigacao-3.0/html_ctrl_panel/loader.api.js");
document.head.appendChild(loadApiScript);