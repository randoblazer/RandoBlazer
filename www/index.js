const e = React.createElement;
const RandomizePhase = 'RandomizePhase';
const DownloadPhase = 'DownloadPhase';
const SeedLabelId = 'randoblazer-seed-label';
const RaceLabelId = 'randoblazer-race-label';
const NoteLabelId = 'randoblazer-note-label';

var ModuleHooks = {
    preRun: function () {},
    print: text => console.log(text),
    printErr: text => console.log(text),
    validRom: false,
};

var Module = {
    preRun: [(function () {
        FS.mkdir('/data');
        FS.mount(IDBFS, {}, '/data');
        FS.syncfs(true, (err) => {
            if (!err) {
                checkExistingROM();
                ModuleHooks.preRun();
            }
        });
    })],
    print: (function () {
        return function (text) {
            ModuleHooks.print(text);
        };
    })(),
    printErr: function (text) {
        if (arguments.length > 1) text = Array.prototype.slice.call(arguments).join(' ');
        console.error("Module call error: " + text);
        ModuleHooks.printErr(text);
    },
    canvas: (function () {
        var canvas = document.getElementById('canvas');
        return canvas;
    })()
};

function checkExistingROM() {
    if (FS.readdir('/data').includes('Soul Blazer.smc')) {
        let result = Module.CheckFile("/data/Soul Blazer.smc");
        ModuleHooks.validRom = result != 0;
    }
}

function romPicker ({validRom, onCheckRom}) {
    let fsInit = FS.readdir('/').includes('/data');
    let initUploaded = fsInit && FS.readdir('/data').includes('Soul Blazer.smc');
    let [romUploaded, setRomUploaded] = React.useState(initUploaded);
    if (!fsInit) {
        ModuleHooks.preRun = () => {
            setRomUploaded(FS.readdir('/data').includes('Soul Blazer.smc'));
            onCheckRom(ModuleHooks.validRom);
        };
    }
    let validClass = '';
    if (romUploaded) {
        validClass = validRom ? 'is-valid' : 'is-invalid';
    }
    let onUpload = function (changeEvent) {
        let file = changeEvent.target.files[0];
        let fileReader = new FileReader();
        fileReader.onload = (loadEvent) => {
            FS.writeFile('/data/Soul Blazer.smc', new Uint8Array(loadEvent.target.result));
            FS.syncfs(false, (err) => {
                checkExistingROM();
                onCheckRom(ModuleHooks.validRom);
                setRomUploaded(true);
            });
        }
        fileReader.readAsArrayBuffer(file);
    }
    let labelText = 'Select ROM';
    if (romUploaded) {
        labelText = validRom ? 'ROM Cached' : 'Invalid ROM';
    }

    return e('div', {class: 'form-control'},
    e('input', {
        type: 'file',
        id: 'rom-file-picker',
        class: validClass + ' form-control d-none',
        onChange: event => onUpload(event),
    }),
    e('label', {class: 'd-block', for: 'rom-file-picker'},
        e('i', {class: "fa-solid fa-check me-2" + (romUploaded && validRom ? '' : ' d-none'), style: {color: '#3beb4c'}}),
        e('i', {class: "fa-solid fa-xmark me-2" + (romUploaded && !validRom ? '' : ' d-none'), style: {color: 'red'}}),
        labelText
    ));
}

function RandoForm ({race, seed, note, onFormChange, onRandomizeButton}) {
    var currentValue = {race, seed};
    let [validRom, setValidRom] = React.useState(Module.validRom);

    var onCheckRom = function (isValid) {
        setValidRom(isValid);
    }
    var seedInput = e('input', {
        type: 'text',
        class: 'form-control',
        id: SeedLabelId,
        defaultValue: seed,
        onChange: event => {
            currentValue.seed = event.target.value;
            onFormChange(currentValue)
        }
    });
    var raceToggle = e('input', {
        type: 'checkbox',
        class: "form-check-input",
        id: RaceLabelId,
        checked: race,
        onChange: event => {
            currentValue.race = event.target.checked;
            onFormChange(currentValue)
        }
    });
    var randomizeButton = e('button', {
        class: 'btn btn-primary',
        onClick: onRandomizeButton,
        disabled: !validRom,
    }, "Randomize");
    var hiddenNote = e('input', {
        type: 'hidden',
        id: NoteLabelId,
        defaultValue: note,
        onChange: event => {
            currentValue.note = event.target.note;
            onFormChange(currentValue)
        }
    });

    let colClass = 'col-lg-8 col-md-8';
    let rowClass = 'row g-3 justify-content-center mt-1';
    return e('div', {class: 'container-fluid my-3'},
        e('div', {class: rowClass},
            e('div', {class: colClass}, e('div', {class: 'input-group'},
                e('label', {class: 'input-group-text', for: 'rom-file-picker'}, "ROM File"),
                e(romPicker, {validRom, onCheckRom})
            ))
        ),
        e('div', {class: rowClass},
            e('div', {class: colClass}, e('div', {class: 'input-group'},
                e('label', {class: 'input-group-text', for: SeedLabelId}, "Seed"),
                seedInput
            ))
        ),
        e('div', {class: rowClass},
            e('div', {class: colClass}, e('div', {class: 'input-group'},
                e('div', {class: "form-check form-switch form-switch-sm"},
                    raceToggle,
                    e('label', {class: "form-check-label mx-2", for: RaceLabelId}, "Race Mode")
                )
            ))
        ),
        hiddenNote,
        e('div', {class: 'text-center mt-3'}, randomizeButton)
    );
}

function DownloadForm ({genSettings, onDownloadBackButton}) {
    let settingsText = genSettings.race ? "race" : "normal";

    let link = [location.protocol, '//', location.host, location.pathname, '?seed=', genSettings.seed].join('');
    if (genSettings.race) {
        link += '&race=true';
    }
    function onCopyLink () {
        if ('clipboard' in navigator) {
            navigator.clipboard.writeText(link);
        } else {
            document.execCommand('copy', true, link);
        }
    }
    let blob, romFileName;
    try {
        blob = new Blob([FS.readFile('/out.smc')], { type: 'application/octet-stream' });
    } catch (err) {
        blob = new Blob();
    }
    if (genSettings.note) {
        romFileName = `Soul Blazer Randomizer - ${genSettings.note} - ${genSettings.seed}.smc`;
    } else {
        romFileName = `Soul Blazer Randomizer - ${genSettings.seed}.smc`;
    }
    let downloadButton = e('a', {download: romFileName, href: URL.createObjectURL(blob)},
        e('button', {class: 'btn btn-primary mx-2'}, "Download ROM")
    );
    let spoilerButton;
    if (!genSettings.race) {
        try {
            blob = new Blob([FS.readFile(`/SpoilerLog.txt`)], { type: 'application/octet-stream' });
        } catch (err) {
            blob = new Blob();
        }
        spoilerButton = e('a', {download: `Soul Blazer Randomizer - ${genSettings.seed} Spoiler.txt`, href: URL.createObjectURL(blob)},
            e('button', {class: 'btn btn-warning mx-2'}, "Download Spoiler")
        );
    }

    return e('div', {},
        e('div', {class: 'my-3'}, 
            e('button', {class: 'btn btn-secondary', onClick: onDownloadBackButton}, "Back to Settings")
        ),
        e('div', {class: 'text-center'}, `Seed: ${genSettings.seed}`),
        e('div', {class: 'text-center'}, `Settings: ${settingsText}`),
        e('div', {class: 'text-center'},
            e('a', {href: link, class: 'd-block'}, link),
            e('button', {class: 'btn btn-secondary me-2', onClick: onCopyLink}, 
                e('i', {class: "fa-regular fa-clipboard mx-2"}),
                "Copy Shareable Link"
            ),
        ),
        e('div', {class: 'download-button-div text-center mt-3'}, downloadButton, spoilerButton)
    );
}

function RandoBlazerMain () {
    var urlParams = new URLSearchParams(location.search);
    let [phase, setPhase] = React.useState(RandomizePhase);
    let [seed, setSeed] = React.useState(urlParams.has('seed') ? urlParams.get('seed') : 0);
    let [race, setRace] = React.useState(urlParams.has('race') ? !!urlParams.get('race') : false);
    let [note, setNote] = React.useState(urlParams.has('note') ? urlParams.get('note') : '');
    let [genSettings, setGenSettings] = React.useState({});
    function onFormChange (newValue) {
        setRace(newValue.race);
        if (newValue.race) {
            urlParams.set('race', 1);
        } else {
            urlParams.delete('race');
        }
        setSeed(newValue.seed);
        if (newValue.seed == 0) {
            urlParams.delete('seed');
        } else {
            urlParams.set('seed', newValue.seed);
        }
        setNote(newValue.note);
        let url = new URL(location);
        url.search = urlParams.toString();
        window.history.replaceState(null, '', url.toString());
    }
    function onRandomizeButton () {
        let convertedSeed = Number(seed);
        convertedSeed = isNaN(convertedSeed) ? 0 : convertedSeed;
        let options = [];
        if (race) {
            options.push('race');
        }
        let actualSeed = Module.Randomize("/data/Soul Blazer.smc", "/out.smc", convertedSeed, options.join(','));
        if (actualSeed.length === 0) {
            // Randomization failed - shouldn't happen hopefully
            return;
        }
        setSeed(actualSeed);
        if (document.getElementById(SeedLabelId)) {
            document.getElementById(SeedLabelId).value = actualSeed;
        }
        urlParams.set('seed', actualSeed);
        let url = new URL(location);
        url.search = urlParams.toString();
        window.history.replaceState(null, '', url.toString());
        setGenSettings({seed: actualSeed, race, note});
        setPhase(DownloadPhase);
    }
    function onDownloadBackButton () {
        setPhase(RandomizePhase);
    }

    return e('div', {class: 'randoblazer-main container'}, 
        e('div', {class: 'row justify-content-center'}, e('div', {class: 'col-md-10 col-lg-8'},
            e('div', {class: phase === RandomizePhase ? '' : 'd-none'},
                e(RandoForm, {race, seed, note, onFormChange, onRandomizeButton})
            ),
            e('div', {class: phase === DownloadPhase ? '' : 'd-none'},
                e(DownloadForm, {genSettings, onDownloadBackButton})
            ) 
        ))
    );
}

function startup () {
    const root = ReactDOM.createRoot(document.getElementById('react-root'));
    root.render(e(RandoBlazerMain));
}

document.addEventListener('DOMContentLoaded', startup);

// Append the contents of randoblazer.js, the js output of the build process here
