function turnGreen()
{
    document.getElementById('colorChangeG').style.backgroundColor = 'green';
}

function turnRed()
{
    document.getElementById('colorChangeR').style.backgroundColor = 'red';
}

function buttons(){
    document.addEventListener('DOMContentLoaded', function() {
    //multiple choice question

    //when right answer clicked, turn green
    let yes = document.querySelector('.yesButton');
    yes.addEventListener('click', function() {
        yes.style.backgroundColor = 'green';
    })
    //when wrong answer turn red
    let no = document.querySelector('.noButton');
    no.addEventListener('click', function() {
        no.style.backgroundColor = 'red';
    })
    });
}