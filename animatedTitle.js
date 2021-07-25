function typeTitle(delay = 300) {
    restoreTitle()
    Title = document.title;
    let counter = Title.length;
    let direction = false;
    typeTitleInterval = setInterval(function () {
        direction = counter == Title.length ? false : counter == false ? true : direction
        counter = (direction == true) ? ++counter : --counter;
        newtitle = (counter == 0) ? "⠀" : Title.slice(0, counter);
        document.title = newtitle;
    }, delay);
}

function scrollTitle(delay = 300, spaces = 20) {
    restoreTitle()
    scroTitleInterval = setInterval(function () {

        Title = document.title;
        let title = document.title;
        let newtitle = [title.slice(0, 0), (title[spaces] === undefined ? "⠀" : title[spaces]), title.slice(0)].join('');
        document.title = newtitle;
    }, delay);
}

function restoreTitle() {
    try {
        document.title = originalTitle;
        clearInterval(typeTitleInterval);
        clearInterval(scroTitleInterval);
    }
    catch { }
}

window.onload = function () {
    let title = document.title;
    document.title = title.replace(" ", "⠀");
    originalTitle = document.title;
}