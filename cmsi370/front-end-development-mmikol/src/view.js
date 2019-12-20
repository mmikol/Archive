(() => {
  const recipeId = parseInt(location.hash.substring(1))

  const setupInfoDisplay = () => {
    (async () => {
      try {
        const recipe = await window.ApiService.getRecipeInfo(recipeId)
        const recipeSteps = recipe.analyzedInstructions[0].steps

        displayGeneralInfo(recipe)
        displayIngredients(recipe.extendedIngredients)
        displayInstructions(recipeSteps, 0)

        let stepOffset = 0

        $('#nextStepButton').click(() => {
          if (stepOffset >= 0 && stepOffset < recipeSteps.length - 1) {
            displayInstructions(recipeSteps, ++stepOffset)
          }
        })

        $('#prevStepButton').click(() => {
          if (stepOffset > 0 && stepOffset < recipeSteps.length) {
            displayInstructions(recipeSteps, --stepOffset)
          }
        })
      } catch (error) {
        $('figure').empty().append(
          $('<div></div>')
            .addClass('col alert alert-danger')
            .text('Sorry, but something went wrong.')
        )
      }

      try {
        const nutritionFacts = await window.ApiService.getNutritionFacts(recipeId)
        displayNutrition(nutritionFacts)
      } catch (error) {
        $('#nutritionTableContainer').empty().append(
          $('<div></div>')
            .addClass('col alert alert-danger')
            .text('Sorry, but something went wrong.')
        )
      }
    })()

    const displayGeneralInfo = (recipe) => {
      $('.recipeImage').attr("src", `${recipe.image}`)
      $('.recipeImage').css('margin-top', `-${$(this).height() / 4}px`)
      $('.recipeImage').css('margin-left', `-${$(this).width() / 5}px`)
      $('.recipeTitle').append(`<h1>${recipe.title}</h1>`)
    }

    const ingredientElement = ingredient => { return `<li>${ingredient.originalString}</li>` }

    const displayIngredients = ingredients => {
      $('#ingredientList').append(ingredients.map(ingredientElement))
      $('#ingredientContainer').css('margin-top', `-${$(this).height() / 4}px`)
    }

    const displayInstructions = (steps, offset) => {
      $('#stepText').text(steps[offset].step)
      $('#stepsContainer').css('margin-top', `-${$(this).height() / 5}px`)
    }

    const displayNutrition = (nutritionFacts) => {
      $('#nutritionTable').append(
        `<tr>
            <td>
              <span class="boldedText"> Calories</span> ${nutritionFacts.calories}
            </td>
            <td>
              <span class="boldedText"> Fat</span> ${nutritionFacts.fat}
            </td>
            <td>
              <span class="boldedText"> Carbs</span> ${nutritionFacts.carbs}
            </td>
            <td>
              <span class="boldedText"> Protein</span> ${nutritionFacts.protein}
            </td>
        </tr>`
      )
    }
  }

  const init = () => {
    setupInfoDisplay()
  }

  window.SpoonacularViewHandler = {
    init
  }
})()