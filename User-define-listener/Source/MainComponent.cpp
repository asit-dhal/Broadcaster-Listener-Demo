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

#include "MainComponent.h"

MainComponent::MainComponent()
{
    addAndMakeVisible(m_inputForm);
    addAndMakeVisible(m_clearButton);
    addAndMakeVisible(m_submitButton);

    m_clearButton.setButtonText("Clear");
    m_submitButton.setButtonText("Submit");
    m_clearButton.setEnabled(false);
    m_submitButton.setEnabled(false);

    m_inputForm.addListener(this);

    m_clearButton.onClick = [this] {m_inputForm.clear(); };
    m_submitButton.onClick = [this] {m_inputForm.submit(); };

    setSize (600, 400);
}

MainComponent::~MainComponent()
{
    m_inputForm.removeListener(this);
}

void MainComponent::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setFont (Font (16.0f));
    g.setColour (Colours::white);
}

void MainComponent::resized()
{
    auto localBounds = getLocalBounds();
    auto buttonArea = localBounds.removeFromBottom(50);

    m_clearButton.setBounds(buttonArea.removeFromLeft(buttonArea.getWidth() / 2).reduced(10));
    m_submitButton.setBounds(buttonArea.reduced(10));

    m_inputForm.setBounds(localBounds.reduced(10, 10));
}

void MainComponent::clearActivated(InputForm*, bool isActive)
{
    m_clearButton.setEnabled(isActive);
}

void MainComponent::submitActivated(InputForm*, bool isActive)
{
    m_submitButton.setEnabled(isActive);
}