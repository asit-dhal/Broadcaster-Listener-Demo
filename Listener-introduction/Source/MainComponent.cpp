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
    addAndMakeVisible(m_valueSlider);
    m_valueSlider.setRange(10, 100); 
    m_valueSlider.setTextValueSuffix(" Cnt");
    m_valueSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);

    addAndMakeVisible(m_sliderLabel);
    m_sliderLabel.setText("Value", dontSendNotification);
    setSize (600, 400);

    m_valueSlider.addListener(this);
}

MainComponent::~MainComponent()
{
    m_valueSlider.removeListener(this);
}

void MainComponent::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setFont (Font (16.0f));
    g.setColour (Colours::white);
}

void MainComponent::resized()
{
    auto sliderLeft = 120;
    m_valueSlider.setBounds(sliderLeft, 20, getWidth() - sliderLeft - 10, 20);
    m_sliderLabel.setBounds(sliderLeft, 50, getWidth() - sliderLeft - 10, 20);
}

void MainComponent::sliderValueChanged(Slider *slider)
{
    if (&m_valueSlider == slider) {
        auto value = slider->getValue();
        m_sliderLabel.setText(String(std::to_string(static_cast<int>(value))), dontSendNotification);
    }
}
