function animateTitle(Title = "Hello, World!", delay = 300) {
    let counter = 0;
    let direction = true;
    aniTitle = setInterval(function () {
        // if (counter == Title.length)
        //     direction = false;
        // if (counter == false)
        //     direction = true;

        direction = counter == Title.length ? false : counter == false ? true : direction

        counter = (direction == true) ? ++counter : --counter;
        newtitle = (counter == 0) ? "⠀" : Title.slice(0, counter);
        document.title = newtitle;
    }, delay)
}