function typeTitle(delay = 300) {
    Title = document.title;
    let counter = Title.length;
    let direction = false;
    typeTitle = setInterval(function () {
        direction = counter == Title.length ? false : counter == false ? true : direction
        counter = (direction == true) ? ++counter : --counter;
        newtitle = (counter == 0) ? "⠀" : Title.slice(0, counter);
        document.title = newtitle;
    }, delay)
}

function scrollTitle(delay = 300, spaces = 15) {
    scrollTitle = setInterval(function () {
        let title = document.title;
        let newtitle = [title.slice(0, 0), (title[spaces] === undefined ? "⠀" : title[spaces]), title.slice(0)].join('');
        document.title = newtitle;
    }, delay)
}