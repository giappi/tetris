#!/usr/bin/node

"use strict";

const PROGRAM_NAME="Tetris";
const PROGRAM_DIR="bin";
const PROJECT_DIR="..";


const FileSystem           = require('fs');
const childProcess         = require('child_process');
const exec                 = childProcess.execSync;
const spawn                = childProcess.spawn;
const crypto               = require('crypto');
const OS                   = require('os');
const readline             = require("readline");


// force ground color
var fg = 
{
    reset : '\x1B[0m',
    black : '\x1B[30m',
    darkred : '\x1B[31m',
    darkgreen : '\x1B[32m',
    orange : '\x1B[33m',
    darkblue : '\x1B[34m',
    purple : '\x1B[35m',
    darkcyan : '\x1B[36m',
    gray : '\x1B[37m',
    darkgray : '\x1B[90m',
    red : '\x1B[91m',
    green : '\x1B[92m',
    yellow : '\x1B[93m',
    blue : '\x1B[94m',
    pink : '\x1B[95m',
    cyan : '\x1B[96m'
};

var print = s => process.stdout.write(s);

var currentLine = 0;

function echo(s, color="")
{
    // clear line if line is new
    if(s.match(/\n$/))
    {
        readline.clearLine(process.stdout, 2);
    }
    
    if(color != "")
    {
        s = color + s + fg.reset;
    }
    print(s);

    return currentLine;
}

function display(s)
{
    readline.cursorTo(process.stdout, 0, null);
    readline.clearLine(process.stdout, 0);
    print("\n");
    print(s);
    readline.cursorTo(process.stdout, 0, null);
    readline.moveCursor(process.stdout, 0, -1);
}

var performance =
{
    "now" : function()
    {
        let t = process.hrtime();
        return t[0] + t[1]/1e9;
    }
};


var remove = function(value, arr)
{
    let index = arr.indexOf(value);
    arr.splice(index, 1);
    return arr;
};


//setup for compile
var sources = scandir(PROJECT_DIR + "/src").filter(file => file.match(/\.cpp$/));
sources.push(PROJECT_DIR + "/lib/stackblur/stackblur.cpp");

var includes = "-I ${PROJECT_DIR}/lib/SDL2/include -I ${PROJECT_DIR}/src".replace("${PROJECT_DIR}", PROJECT_DIR);
var libraries = "../lib/SDL2/lib/emscripten/libSDL2.bc";
var flags = "-O3 -g -std=c++11";
var cc = "em++";
if(OS.platform() == "win32")
{
    cc = "em++.bat";
}


// setup for link program
var programName = "-o bin/Tetris.html";
var link = "em++";
var link_flags = "";
var link_options = "-O3 -s WASM=0 -s ALLOW_MEMORY_GROWTH=1 --use-preload-plugins --preload-file ../res@/res --shell-file template/to-yeu-cau.html";

echo ("\n");
echo ("-- Compiling --\n\n", fg.cyan);

var objects = [];
var build = true;

var commands = [];
var cp_times = [];

for(let i in sources)
{
    let c = sources[i];
    let o = "obj/" + i + ".bc";
    objects.push(o);
    commands.push({file: c , line: [cc, ...flags.split(" ") , "-c" , c , ...includes.split(" "), "-o" , o ]});

}

var uncompiled_files = commands.length;
var uncached_files = uncompiled_files;
var compiling_files = [];

function compile()
{
    if(commands.length > 0)
    {
        let command     = commands.pop();
        let id          = commands.length;
        let file        = command.file;
        let cacheObj    = "obj/" + id + ".cache";
        let onCompleted = function(id, is_cached)
        {
            var t1 = cp_times[id];
            var t2 = performance.now();
            var time = Math.round((t2 - t1)*1000)/1000;
            echo(`    Compiled ${fg.pink}"${command.file}"${fg.reset}`);
            uncompiled_files--;
            remove(command.file, compiling_files);

            if(is_cached)
            {
                echo(` ${fg.darkgray}(cached)${fg.reset}`);
                uncached_files--;
            }
            else
            {
                echo(` ${fg.orange}(${time}s)${fg.reset} ${fg.green}(success)${fg.reset}`);
            }
            echo("\n");
            if(uncompiled_files < 1)
            {
                linkProgram();
                return;
            }
            else
            {
                // execute next command
                compile();
            }

        };
        
        if(!fileExists(cacheObj) || (fileExists(file) && (md5f(cacheObj) != md5f(file))))
        {

            compiling_files.push(command.file);
            display(`Compiling ... ${id} files: ${fg.yellow}${compiling_files[0]}${fg.reset}`);

            cp_times[id] = performance.now();
            // stdio: "inherit" to keep color by child process
            let child_process = spawn(command.line[0], command.line.slice(1) , {stdio: "inherit", encoding: "utf-8" });
            
            child_process.on("error", function(e) { echo("[E]" + e);});
            child_process.on('close', function(exitcode)
            {
                if(exitcode == 0)
                {
                    onCompleted(id, false);
                    copyfile(file, cacheObj);
                }
                else
                {
                    echo("[E] Compile Error\n", fg.red);
                }
            });
        }
        else
        {
            onCompleted(id, true);
        }

    }
}

{
    if(!fileExists("obj"))
    {
        FileSystem.mkdirSync("obj");
    }
    // 4 process at the same time
    for(var i = 0; i < 1; i++)
    {
        compile();
    }
}


function linkProgram()
{
    
    echo("\n");
    echo("-- BUILD COMPLETE --\n\n");
    
    var link_cmd = [link, link_flags, link_options , objects.join(" "), libraries, programName].join(" ");
    
    echo ("\n");
    echo ("-- Linking program --\n", fg.cyan);
    //if(uncached_files > 0)
    {
        exec(link_cmd);
    }
    echo ("-- Done --\n\n", fg.cyan);
}


///////////////////////////////////////////////////////////////////

function scandir(dir)
{
    var result = [];
    var list = FileSystem.readdirSync(dir).map(file => dir + "/" + file);
    while(list.length > 0)
    {
        var file = list.pop();
        if(FileSystem.lstatSync(file).isDirectory())
        {
            var t = FileSystem.readdirSync(file);
            for(var child of t)
            {
                list.push(file + "/" + child);
            }
        }
        else
        {
            result.push(file);
        }
    }
    return result;
}

function copyfile(source, target)
{
    FileSystem.createReadStream(source).pipe(FileSystem.createWriteStream(target));
}

function fileExists(file)
{
    return FileSystem.existsSync(file);
}

function md5f(file)
{
    var data = FileSystem.readFileSync(file);
    return crypto.createHash('md5').update(data).digest("hex");
}

///////////////////////////////////////////////////////////////////