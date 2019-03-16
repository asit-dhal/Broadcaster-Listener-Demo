/*
 * Copyright (c) 2019 Asit Dhal.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "InputForm.h"

InputForm::InputForm()
{
    addAndMakeVisible(m_usernameLabel);
    m_usernameLabel.setText("Username:", dontSendNotification);
    m_usernameLabel.attachToComponent(&m_usernameInput, true);
    m_usernameLabel.setColour(Label::textColourId, Colours::orange);
    m_usernameLabel.setJustificationType(Justification::right);

    addAndMakeVisible(m_passwordLabel);
    m_passwordLabel.setText("Password:", dontSendNotification);
    m_passwordLabel.attachToComponent(&m_passwordInput, true);
    m_passwordLabel.setColour(Label::textColourId, Colours::orange);
    m_passwordLabel.setJustificationType(Justification::right);

    addAndMakeVisible(m_usernameInput);
    m_usernameInput.setEditable(true);
    m_usernameInput.setColour(Label::backgroundColourId, Colours::darkblue);
    m_usernameInput.setJustificationType(Justification::left);

    addAndMakeVisible(m_passwordInput);
    m_passwordInput.setEditable(true);
    m_passwordInput.setColour(Label::backgroundColourId, Colours::darkblue);
    m_passwordInput.setJustificationType(Justification::left);

    m_clearActive = false;
    m_submitActive = false;

    m_usernameInput.addListener(this);
    m_passwordInput.addListener(this);
}

InputForm::~InputForm()
{
    m_usernameInput.removeListener(this);
    m_passwordInput.removeListener(this);
}

void InputForm::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);

}

void InputForm::resized()
{
    auto marginX = 10;
    auto marginY = 10;
    auto localBounds = getLocalBounds();

    auto usernameRect = localBounds.removeFromTop(50);
    m_usernameLabel.setBounds(usernameRect.removeFromLeft(usernameRect.getWidth() / 5).reduced(marginX, marginY));
    m_usernameInput.setBounds(usernameRect.reduced(marginX, marginY));

    auto passwordRect = localBounds.removeFromTop(50);
    m_passwordLabel.setBounds(passwordRect.removeFromLeft(passwordRect.getWidth() / 5).reduced(marginX));
    m_passwordInput.setBounds(passwordRect.reduced(marginX, marginY));
}


void InputForm::addListener(Listener* listenerToAdd)
{
    m_listeners.add(listenerToAdd);
}

void InputForm::removeListener(Listener* listenerToRemove)
{
    jassert(m_listeners.contains(listenerToRemove));
    m_listeners.remove(listenerToRemove);
}

void InputForm::clearActivate(bool isActive)
{
    m_listeners.call([this, isActive](Listener& l) { l.clearActivated(this, isActive); });
}

void InputForm::submitActivate(bool isActive)
{
    m_listeners.call([this, isActive](Listener& l) { l.submitActivated(this, isActive); });
}

void InputForm::labelTextChanged(Label *labelThatHasChanged)
{
    bool atLeastOneTextFilled = false;

    if (labelThatHasChanged == &m_usernameInput) {
        atLeastOneTextFilled = !m_usernameInput.getText(false).isEmpty();
    }
    else if (labelThatHasChanged == &m_passwordInput) {
        atLeastOneTextFilled = !m_passwordInput.getText(false).isEmpty();
    }

    if (!m_clearActive && atLeastOneTextFilled) {
        m_clearActive = true;
        clearActivate(true);
    }
    else if (m_clearActive && !atLeastOneTextFilled) {
        m_clearActive = false;
        clearActivate(false);
    }

    bool allTextFilled = !m_usernameInput.getText(true).isEmpty() && !m_passwordInput.getText(true).isEmpty();
    if (!m_submitActive && allTextFilled) {
        m_submitActive = true;
        submitActivate(true);
    }
    else if (m_submitActive && !allTextFilled) {
        m_submitActive = false;
        submitActivate(false);
    }
}

void InputForm::submit()
{
    // do nothing
}
void InputForm::clear()
{
    m_usernameInput.setText("", NotificationType::sendNotification);
    m_passwordInput.setText("", NotificationType::sendNotification);
}