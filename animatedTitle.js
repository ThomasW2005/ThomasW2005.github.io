function animateTitle(Title = "Hello, World!", delay = 300) {
    let counter = Title.length;
    let direction = false;
    aniTitle = setInterval(function () {
        direction = counter == Title.length ? false : counter == false ? true : direction
        counter = (direction == true) ? ++counter : --counter;
        newtitle = (counter == 0) ? "⠀" : Title.slice(0, counter);
        document.title = newtitle;
    }, delay)
}